#include "searcher.h"

Searcher::Searcher():cell_size(VECT(CELL_SIZE, CELL_SIZE)),
    font_size(cell_size.y*1.5){
        if(!font.loadFromFile("fonts/Azbuka.ttf"))
        cout<<"Error font loading"<<endl;
        s_cursor = 0;
        start_index = 0;
}

void Searcher::search_display(){
    search_results.create(sf::VideoMode(WINDOW_SIZE, 0.5*WINDOW_SIZE), "Search results");
    search_win_size = VECT(search_results.getSize().x/cell_size.x, search_results.getSize().y/cell_size.y);
    str_count = (search_win_size.y - 14) / 2;
    while (search_results.isOpen()){
        sf::Event event;
        while (search_results.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                path_to_go.erase();// no action
                search_results.close();                 
            }
                   
            if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){

                    case sf::Keyboard::Up:
                        if(!(s_cursor-1<0))
                            s_cursor--;             
                        if(s_cursor < start_index){
                            start_index = s_cursor;
                            } 
                    break;

                    case sf::Keyboard::Down:
                        if(s_cursor+1<found.size())
                            s_cursor++;             
                        if(s_cursor > start_index + str_count-1)    
                            start_index++;  
                    break;

                    case sf::Keyboard::Return:{         
                        path_to_go = found[s_cursor];
                        search_results.close();
                    break;}

                    case sf::Keyboard::Escape:
                        path_to_go.erase();// no action
                        search_results.close();
                    break;
                }
            }    
        }
        search_draw();
        search_results.display();
    }
}

void Searcher::search_draw(){
    sf::RectangleShape bg(VECT(search_win_size.x*cell_size.x, search_win_size.y*cell_size.y));
    bg.setFillColor(sf::Color(15,15,15));
    search_results.draw(bg);
    sf::RectangleShape rect(cell_size);
    rect.setFillColor(sf::Color(240, 248, 255));
    for(int x = 0; x < search_win_size.x; x++){    //horisontal borders
        rect.setPosition(x * cell_size.x, 0);
        search_results.draw(rect);
        rect.setPosition(x * cell_size.x, (search_win_size.y - 1)* cell_size.y);
        search_results.draw(rect);
    }
    for(int y = 0; y < search_win_size.y; y++){    //vertical borders
        rect.setPosition(0, y*cell_size.y);
        search_results.draw(rect);
        rect.setPosition((search_win_size.x - 1)* cell_size.x, y * cell_size.y);
        search_results.draw(rect);
    }
    sf::RectangleShape hilight(VECT((search_win_size.x - 2)* cell_size.x, 2* cell_size.y));
    hilight.setFillColor(sf::Color(104,105,105));
    VECT line(1, 1);
    for(int i = start_index; i < start_index+(str_count<found.size()?str_count:found.size()); i++){
        if(s_cursor  == i){
            hilight.setPosition(line.x*cell_size.x, line.y*cell_size.y);
            search_results.draw(hilight);
        }
        draw_text(search_results, found[i], line);
        line.y+=2;
    }
}

void Searcher::draw_text(sf::RenderWindow &window, string textP, VECT position){
    sf::Text text(textP, font);
    text.setCharacterSize(font_size);
    text.setFillColor(sf::Color::Green);
    text.setPosition(cell_size.x*(position.x + 0.25), cell_size.y*(position.y + 0.25));
    window.draw(text);
}
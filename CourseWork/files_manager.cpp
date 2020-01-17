#include "files_manager.h"

files_manager::files_manager(sf::RenderWindow &window):cell_size(VECT(CELL_SIZE, CELL_SIZE)),
    win_size(VECT(window.getSize().x/cell_size.x, window.getSize().y/cell_size.y)), font_size(cell_size.y*1.5),
    str_count((win_size.y - 14) / 2), display_console(Menu_console::NO),searcher(){
    if(!font.loadFromFile("fonts/Azbuka.ttf"))
        cout<<"Error font loading"<<endl;
    bordColor = sf::Color(240, 248, 255);
    activePanel = &leftPanel;

    text.setCharacterSize(font_size);
    text.setFont(font);
}

void files_manager::Explore(sf::RenderWindow &window){
    sf::RectangleShape bg(VECT(win_size.x*cell_size.x, win_size.y*cell_size.y));
    bg.setFillColor(sf::Color(15,15,15));
    window.draw(bg);
    draw_table(window);
    draw_hb(window);
    draw_panel(window);
    if(display_console){
        draw_text(window,"Enter the name:", VECT(1, win_size.y - 5));        
        draw_text(window, console_line, VECT(1, win_size.y - 3));
    }
}

void files_manager::draw_panel(sf::RenderWindow &window){
    sf::RectangleShape rect(cell_size);
    rect.setFillColor(sf::Color(31,31,31));
        if(activePanel==&leftPanel){
            for(int x = 1; x < win_size.x/2 - 1; x++){
                rect.setPosition(x * cell_size.x, cell_size.y);
                window.draw(rect);
                rect.setPosition(x * cell_size.x, 2*cell_size.y);
                window.draw(rect);
            }
            for(int x = 1; x < win_size.x/2 - 1; x++){
                for(int y = 4; y <  win_size.y - 10; y++){
                    rect.setPosition(x * cell_size.x, y * cell_size.y);
                    window.draw(rect);
                }
            }
        }
        else{
            for(int x = win_size.x/2 + 1; x < win_size.x - 1; x++){
                rect.setPosition(x * cell_size.x, cell_size.y);
                window.draw(rect);
                rect.setPosition(x * cell_size.x, 2*cell_size.y);
                window.draw(rect);
            }
            for(int x = win_size.x/2 + 1; x < win_size.x - 1; x++){
                for(int y = 4; y <  win_size.y - 10; y++){
                    rect.setPosition(x * cell_size.x, y * cell_size.y);
                    window.draw(rect);
                }
            }
        }


    draw_text(window, leftPanel.current_directory, VECT(1,1));
    draw_text(window, rightPanel.current_directory, VECT(win_size.x/2 + 1,1));

    VECT line(1, 4);
    sf::RectangleShape hilight(VECT((win_size.x/2 - 2)* cell_size.x, 2* cell_size.y));
    hilight.setFillColor(sf::Color(104,105,105));

    //draw leftPanel.content
    for(int i = leftPanel.start_index;
        i<leftPanel.start_index+(str_count<leftPanel.content.size()?str_count:leftPanel.content.size());
        i++){
            if(leftPanel.cursor  == i && activePanel==&leftPanel){
                hilight.setPosition(line.x*cell_size.x, line.y*cell_size.y);
                window.draw(hilight);
            }
            draw_text(window, leftPanel.content[i].name, line);
            draw_text(window, leftPanel.content[i].time, VECT(line.x + 25, line.y));
            draw_text(window, leftPanel.content[i].size, VECT(win_size.x/2 - 1 - leftPanel.content[i].size.size(), line.y));
            line.y+=2;
        }

    line = VECT(win_size.x/2 + 1, 4);

    //draw rightPanel.content
    for(int i = rightPanel.start_index;
        i<rightPanel.start_index+(str_count<rightPanel.content.size()?str_count:rightPanel.content.size());
        i++){
            if(rightPanel.cursor  == i && activePanel==&rightPanel){
                hilight.setPosition(line.x*cell_size.x, line.y*cell_size.y);
                window.draw(hilight);
            }
            draw_text(window, rightPanel.content[i].name, line);
            draw_text(window, rightPanel.content[i].time, VECT(line.x + 25, line.y));
            draw_text(window, rightPanel.content[i].size, VECT(win_size.x - 1 - rightPanel.content[i].size.size(), line.y));
            line.y+=2;
        }
}

void files_manager::draw_hb(sf::RenderWindow &window){
    int tab=15;
    VECT pos(1, win_size.y - 9);
    draw_text(window, "NewFolder\tF3\0", pos);
    pos.x += tab;
    draw_text(window, "Rename\tF4\0", pos);
    pos.x += tab;
    draw_text(window, "Copy\tF5\0", pos);
    pos.x += tab;
    draw_text(window, "Move\tF6\0", pos);
    pos.x += tab;   
    draw_text(window, "Search\tF7\0", pos);
    pos.x += tab;
    draw_text(window, "Delete\tF8\0", pos);
    
}

void files_manager::draw_table(sf::RenderWindow &window){
    sf::RectangleShape rect(cell_size);
    rect.setFillColor(bordColor);
    for(int x = 0; x < win_size.x; x++){    //horisontal borders
        rect.setPosition(x * cell_size.x, 0);
        window.draw(rect);
        rect.setPosition(x * cell_size.x, (win_size.y - 1)* cell_size.y);
        window.draw(rect);
    }
    for(int y = 0; y < win_size.y; y++){    //vertical borders
        rect.setPosition(0, y*cell_size.y);
        window.draw(rect);
        rect.setPosition((win_size.x - 1)* cell_size.x, y * cell_size.y);
        window.draw(rect);
    }
    for(int x = 0; x < win_size.x; x++){    //cur_dir line and help_box separator
        rect.setPosition(x* cell_size.x, 3*cell_size.y);
        window.draw(rect);
        rect.setPosition(x* cell_size.x, (win_size.y - 10)* cell_size.y);
        window.draw(rect);
    }
    for(int y = 0; y <  win_size.y - 10; y++){  //panel separator
        rect.setPosition((win_size.x/2)* cell_size.x, y*cell_size.y);
        window.draw(rect);
        rect.setPosition((win_size.x/2 - 1)* cell_size.x, y * cell_size.y);
        window.draw(rect);
    }
}

void files_manager::draw_text(sf::RenderWindow &window, string textP, VECT position){
    text.setString(textP);   
    text.setFillColor(sf::Color::Green);
    text.setPosition(cell_size.x*(position.x + 0.25), cell_size.y*(position.y + 0.25));
    window.draw(text);
}

//for russian languge use L"Сообщение "
void files_manager::draw_text(sf::RenderWindow &window, wstring textP, VECT position){    
    text.setString(textP);   
    text.setFillColor(sf::Color::Green);
    text.setPosition(cell_size.x*(position.x + 0.25), cell_size.y*(position.y + 0.25));
    window.draw(text);
}

void files_manager::Navigator(sf::Event event){
    if(!display_console){            
        switch(event.key.code){

            case sf::Keyboard::Escape:
                if(display_console != Menu_console::NO){
                    display_console = Menu_console::NO;
                    console_line.erase();
                }
                else
                    activePanel->logical_drives();
            break;

            case sf::Keyboard::Up:
                if(!(activePanel->cursor-1<0))
                    activePanel->cursor--;             
                if(activePanel->cursor < activePanel->start_index)
                    activePanel->start_index=activePanel->cursor;
            break;

            case sf::Keyboard::Down:
                if(activePanel->cursor+1<activePanel->content.size())
                    activePanel->cursor++;             
                if(activePanel->cursor > activePanel->start_index + str_count-1)        
                    activePanel->start_index++;                     
            break;

            case sf::Keyboard::Left:
                change_panel();
            break;

            case sf::Keyboard::Right:
                change_panel();
            break;

            case sf::Keyboard::Return:         
                if(activePanel->is_current_Directory())
                    activePanel->change_dir(activePanel->folders_to_display[activePanel->cursor].name);
                else                   
                   run_fileApp(activePanel->current_directory+'\\'+ activePanel->files_to_display[activePanel->cursor-activePanel->folders_to_display.size()].name);
            break;

            case sf::Keyboard::F3:
                display_console = Menu_console::NEW;
            break;
            
            case sf::Keyboard::F4:
                display_console = Menu_console::RENAME;
            return;

            case sf::Keyboard::F5:{
                string from_dir = activePanel->current_directory;
                string name;
                if(activePanel->is_current_Directory())
                    name = activePanel->folders_to_display[activePanel->cursor].name;
                else
                    name = activePanel->files_to_display[activePanel->cursor - activePanel->folders_to_display.size()].name;
                change_panel();
                activePanel->copy(from_dir, name);
                reload_panels();
            break;}

            case sf::Keyboard::F6:{
                string from_dir = activePanel->current_directory;
                string name;
                if(activePanel->is_current_Directory())
                    name = activePanel->folders_to_display[activePanel->cursor].name;
                else
                    name = activePanel->files_to_display[activePanel->cursor - activePanel->folders_to_display.size()].name;
                change_panel();
                activePanel->move(from_dir, name);
                reload_panels();
            break;}

            case sf::Keyboard::F7:
                display_console = Menu_console::SCAN;
            break;
            
            case sf::Keyboard::F8:
                activePanel->del();
            break;;
        }
    }
    else{if(event.key.code == sf::Keyboard::Escape){
           display_console = Menu_console::NO;
           console_line.erase();
        }
        else if(event.key.code == sf::Keyboard::Return){
            switch(display_console) {
                case Menu_console::NEW:                    
                    activePanel->create_dir(console_line);
                    reload_panels();
                break;

                case Menu_console::RENAME:                   
                    activePanel->rename(console_line);
                    reload_panels();                    
                break;

                case Menu_console::SCAN:                   
                    vector<string> found;
                    activePanel->search(console_line, found);
                    if(!found.empty()){
                        searcher.found = found;
                        searcher.search_display();
                        if(!searcher.path_to_go.empty()){
                            if(searcher.path_to_go.back() == '\\'){
                            activePanel->logical_drives();
                            std::size_t foundp = searcher.path_to_go.find_last_of("\\");
                            activePanel->change_dir(searcher.path_to_go.substr(0, foundp));
                            }
                            else{ 
                                run_fileApp(searcher.path_to_go);
                            }
                        }                     
                    }
                    else
                        MessageBox( NULL,TEXT("No results"),TEXT("Search"),MB_ICONINFORMATION |MB_OK);                    
                    searcher.path_to_go.erase();
                break;
            }

            display_console = Menu_console::NO;
            console_line.erase();
        }
    }
}

void files_manager::reload_panels(){

    string temp = activePanel->current_directory;

    if(temp != "Disks"){
        activePanel->logical_drives();
        std::size_t foundp = temp.find_last_of('\\');
        activePanel->change_dir(temp.substr(0, foundp));
    }

    change_panel();
    temp = activePanel->current_directory;

    if(temp != "Disks"){
        activePanel->logical_drives();
        std::size_t foundp = temp.find_last_of('\\');
        activePanel->change_dir(temp.substr(0, foundp));
    }
    change_panel();
}

void files_manager::change_panel(){
    if(activePanel == &leftPanel)
        activePanel = &rightPanel;
    else
        activePanel = &leftPanel;
}

void files_manager::inputText(sf::Event event){
    // NO=0, NEW=1,  SCAN=2, RENAME=3
    if(display_console){
        if(event.key.code =='\b' && !console_line.empty()){
            console_line.pop_back();
        } 
        else{ 
            char buffer[2];
            wchar_t strW[2];   
            strW[0]=static_cast<wchar_t>(event.text.unicode);
            wcstombs (buffer,   strW, sizeof(buffer));
            if(strpbrk(buffer,"<>:\"\\|/?*")==NULL)
                console_line.push_back(buffer[0]);
            else{
                MessageBox( NULL,
                    TEXT("File and directory names can not contain the following characters \n\t\" <>:\"\\|/?* \" !"),                                    
                    TEXT("Input text"),
                    MB_ICONWARNING |MB_OK);
            }
        }
    }   
}

void files_manager::run_fileApp(string path){    
    HINSTANCE result = ShellExecute(NULL,NULL,path.c_str(),NULL,NULL,SW_RESTORE);
    long long sig1 = reinterpret_cast<long long> (result);
    int sig = static_cast<int>(sig1);
    if(sig < 32){
        MessageBox( NULL,TEXT("Ooops!  There is some problem!"),TEXT("Open file"),MB_ICONWARNING | MB_OK);
        //https://msdn.microsoft.com/en-us/library/windows/desktop/bb762153(v=vs.85).aspx
        //all return code -which problem
    }  
}
#pragma once
#include "headers.h"
#include "panel.h"
#include "searcher.h"

enum Menu_console{
    NO=0,
    NEW,
    SCAN,
    RENAME
};

class files_manager{
    public:
        files_manager(sf::RenderWindow &window);
        void Explore(sf::RenderWindow &window);
        void Navigator(sf::Event event);
        void inputText(sf::Event event);

    private:
        sf::Text text;
        sf::Font font;
        sf::Color bordColor;
        VECT cell_size;
        VECT win_size;
        float font_size;
        int str_count;

        string console_line;

        Menu_console display_console;
        
        Panel leftPanel;
        Panel rightPanel;
        Panel* activePanel;
        Searcher searcher;

        void draw_table(sf::RenderWindow &window);
        void draw_panel(sf::RenderWindow &window);
        void draw_text(sf::RenderWindow &window,wstring textP, VECT position);
        void draw_text(sf::RenderWindow &window,string textP, VECT position);
        void draw_hb(sf::RenderWindow &window);
        void reload_panels();
        void change_panel();
        void run_fileApp(string path);
};

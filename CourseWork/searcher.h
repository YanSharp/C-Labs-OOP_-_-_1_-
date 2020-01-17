#pragma once
#include "headers.h"
#include "panel.h"

class Searcher{
    public:
        vector<string> found;
        string path_to_go;

        Searcher();
        void search_display();

    private:
        sf::RenderWindow search_results;
        int s_cursor;
        int start_index;
        VECT cell_size;
        VECT search_win_size;
        float font_size;
        sf::Font font;
        int str_count;

        void search_draw();
        void draw_text(sf::RenderWindow &window, string textP, VECT position);
};


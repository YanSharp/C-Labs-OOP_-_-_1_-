#pragma once
#include "head.h"

class Texture_pool {
public:
    map<int, sf::Texture> textures;

    static Texture_pool& Instance(){
        static Texture_pool s;
        return s;
    }

private:
    Texture_pool();
    //~Texture_pool();

    Texture_pool(Texture_pool const&) = delete;
    Texture_pool& operator= (Texture_pool const&) = delete;
};
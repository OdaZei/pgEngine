#pragma once 
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteSheet {
    public:
        SpriteSheet();
        SpriteSheet(int, int);
        ~SpriteSheet();
        bool loadResources();
        // @Params: x,y,w,h
        // Get sprite at (x,y) dim (w,h);
        sf::Texture* getTile( int, int, int, int );
    private:
        int defSprWidth;
        int defSprHeight;
        const char* filepath;

        sf::Texture*    texture;
        sf::Image*      image;
};
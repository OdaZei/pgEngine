#pragma once

//DG
#include "SimplexNoise.hpp"
#include "ResourcesManager.hpp"
//@Debug
#include <SFML/Graphics/Image.hpp>

//Defining visible portion, and dimension we will be rendering;

const unsigned int W  = 16;
const unsigned int H  = 16;

const unsigned int CW = 8;
const unsigned int CH = 8;

class World {
    public:
        World();
        World(float xOrigin, float yOrigin,float freq, float ampl, float lac, float pers);
        ~World();
        bool buildImage(size_t octaves, unsigned int shiftX, unsigned int shiftY);
        sf::Sprite getMapImage(int, int, int, float, float);
        
        bool updateWorldView( int, int ); 
        bool pixelsToSpriteImage(int pixels[CW][CW]);
    protected:
        int pixelToId[W][H];
    private:
        //@Debug
        sf::Vector2f    origin;
        sf::Image       displaymap;
        sf::Texture     tex;
        sf::Sprite      spr;
        sf::Sprite      tiledSpr;
        SimplexNoise*   generator;
        SpriteSheet*    sprSheet;
};
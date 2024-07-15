#pragma once

//DG
#include "SimplexNoise.hpp"
#include "ResourcesManager.hpp"
//@Debug
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

//Defining visible portion, and dimension we will be rendering;

const unsigned int W  = 64;
const unsigned int H  = 64;

const unsigned int CW = 32;
const unsigned int CH = 32;

class World {
    public:
        World();
        World(float xOrigin, float yOrigin,float freq, float ampl, float lac, float pers);
        ~World();
        bool buildImage(size_t octaves, unsigned int shiftX, unsigned int shiftY);
        bool getMapImage( int, int, float, float);
        bool updateWorldView( int, int ); 
        bool pixelsToSpriteImage(std::vector<std::vector<int>> pixels);
        void drawmap(sf::RenderTarget* , sf::RenderStates);
    protected:
        std::vector<std::vector<int>> pixelToId;
    private:
        //@Debug
        sf::Vector2f    origin;
        sf::Image       displaymap;
        sf::Texture     tex;
        sf::Sprite      spr;
        SimplexNoise*   generator;
        SpriteSheet*    sprSheet;
};
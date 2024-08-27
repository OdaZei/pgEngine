#pragma once

//DG
#include "SimplexNoise.hpp"
#include "ResourcesManager.hpp"
//@Debug
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

//Defining visible portion, and dimension we will be rendering;

const unsigned int W  = 16;
const unsigned int H  = 16;

const unsigned int CW = 16;
const unsigned int CH = 16;

class World {
    public:
        World( SpriteSheet *);

        World(float, float,float, float, float, float, SpriteSheet *);
        
        ~World();
        
        bool buildImage(size_t , unsigned int , unsigned int, unsigned int);
        bool getMapImage( int, int, float, float, int);
        bool updateWorldView( int, int ); 
        bool pixelsToSpriteImage(std::vector<std::vector<int>> pixels);
        
        void drawmap(sf::RenderTarget* , sf::RenderStates);
        
        std::vector<int> getTile(int,int,Collider);

    protected:
        std::vector<std::vector<int>> pixelToId;
    private:
        //@Debug
        sf::Vector2f        origin;
        sf::Image           displaymap;
        sf::Texture         tex;
        sf::Sprite          spr;
        SimplexNoise*       generator;
        SpriteSheet*        sprSheet;
        sf::Transformable   transform;
};
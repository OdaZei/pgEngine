#pragma once 
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class SpriteSheet {
    public:
        SpriteSheet();
        SpriteSheet(std::vector<std::vector<int>>, int, int);
        ~SpriteSheet();
        bool loadResources(std::vector<std::vector<int>>);
        // @Params: x,y,w,h
        // Get sprite at (x,y) dim (w,h);
        sf::VertexArray getTiles();
        sf::Texture*  getTexture();
    private:
        int defSprWidth;
        int defSprHeight;
        unsigned int tWidth;
        unsigned int tHeight; 
        const char* filepath;

        sf::VertexArray mVertex;
        sf::Texture*    mTexture;
        //sf::Image*      image;
};
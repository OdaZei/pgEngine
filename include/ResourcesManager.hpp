#pragma once 
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <vector>
#include "Tile.hpp"


static const unsigned int nTriangles = 6;
class SpriteSheet {
    public:
        SpriteSheet( );
        SpriteSheet( std::vector<std::vector<int>> , int , int );
        ~SpriteSheet( );
        
        //@DBG: This some massive bullshit@
        bool computeMap(std::vector<std::vector<int>>);

        bool loadResources(std::vector<std::vector<int>>);

        void update(std::vector<std::vector<int>>, int, int);
        
        /* @Params: x,y,w,h */
        /* Get sprite at (x,y) dim (w,h);*/
        void setTileMap( std::vector<std::vector<int>> );
        
        /*DBG*/
        std::vector<int> getnearestTiles( int, int , std::vector<Tile*>& );
        sf::VertexArray getTiles();
        sf::Texture*  getTexture();
        /*DBG*/
        
        //@> params : x , y , index , tile;
        // calls get vertex(arr) , saves it , modifies index reference, returns vertex(arr)
        bool  setTextureSlice( int, int , unsigned int& , int);

        sf::VertexArray  getTextureSlice( unsigned int );

        std::vector< sf::VertexArray > setAnimationSlice(int x, int y, unsigned int& index, int tile, unsigned int animSz );
        std::vector<std::vector<Tile*>>  tiles;
    protected:
        //Gets vertex 
        sf::VertexArray getVertex( int x, int y, int tx, int ty );
    private:
        int defSprWidth;
        int defSprHeight;

        unsigned int tWidth;
        unsigned int tHeight;
        
        const char* filepath;

        sf::VertexArray mVertex; // WorldMap Vertex;

        std::vector<sf::VertexArray> mBuffers; // Entities vertex;
        sf::Texture*    mTexture;
        //sf::Image*      image;
};
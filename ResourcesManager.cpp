#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "include/ResourcesManager.hpp"
#include "include/filepaths.hpp"

SpriteSheet::SpriteSheet( ): defSprWidth(_DEFAULT_TEXTURE_WIDTH_), defSprHeight(_DEFAULT_TEXTURE_HEIGHT_)\
,tWidth(_DEFAULT_TEXTURE_WIDTH_),tHeight(_DEFAULT_TEXTURE_HEIGHT_), filepath(spriteSheet), mTexture(nullptr){
    mTexture = new sf::Texture( );
}
SpriteSheet::SpriteSheet( std::vector<std::vector<int>> arr, int w, int h ): defSprWidth(_DEFAULT_TEXTURE_WIDTH_), defSprHeight(_DEFAULT_TEXTURE_HEIGHT_)\
,tWidth(w),tHeight(h), filepath(spriteSheet), mTexture(nullptr) {
    mTexture = new sf::Texture();
    loadResources(arr);
}
SpriteSheet::~SpriteSheet(){ }
bool SpriteSheet::loadResources( std::vector<std::vector<int>> arr) {
    int nTiles = 4;
    if(!mTexture->loadFromFile(filepath)) return false;
    mVertex.setPrimitiveType(sf::Triangles);
    mVertex.resize( 6 * tWidth * tHeight);
    for( int i = 0; i < tWidth ; i++ ){ 
        for( int j = 0; j < tHeight; j++ ){
            int tile = arr[i][j];
            int tx = tile % nTiles;
            int ty = tile / nTiles;
            sf::Vertex* triangles = &mVertex[(i + j*tWidth)*6];
            triangles[0].position = sf::Vector2f(i * defSprWidth, j * defSprHeight);
            triangles[1].position = sf::Vector2f((i + 1) * defSprWidth, j * defSprHeight);
            triangles[2].position = sf::Vector2f(i * defSprWidth, (j + 1) * defSprHeight);
            triangles[3].position = sf::Vector2f(i * defSprWidth, (j + 1) * defSprHeight);
            triangles[4].position = sf::Vector2f((i + 1) * defSprWidth, j * defSprHeight);
            triangles[5].position = sf::Vector2f((i + 1) * defSprWidth, (j + 1) * defSprHeight);

            triangles[0].texCoords = sf::Vector2f(tx * defSprWidth, ty * defSprHeight);
            triangles[1].texCoords = sf::Vector2f((tx + 1) * defSprWidth, ty * defSprHeight);
            triangles[2].texCoords = sf::Vector2f(tx * defSprWidth, (ty + 1) * defSprHeight);
            triangles[3].texCoords = sf::Vector2f(tx * defSprWidth, (ty + 1) * defSprHeight);
            triangles[4].texCoords = sf::Vector2f((tx + 1) * defSprWidth, ty * defSprHeight);
            triangles[5].texCoords = sf::Vector2f((tx + 1) * defSprWidth, (ty + 1) * defSprHeight);
        }
    }
    return true;
}
sf::VertexArray SpriteSheet::getTiles( ) {
    return mVertex;
}
sf::Texture* SpriteSheet::getTexture( ) {
    return mTexture;
}


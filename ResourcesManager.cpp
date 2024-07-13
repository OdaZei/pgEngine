#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "include/ResourcesManager.hpp"
#include "include/filepaths.hpp"

SpriteSheet::SpriteSheet( ): defSprWidth(8), defSprHeight(8)\
, filepath(spriteSheet), texture(nullptr), image( nullptr) {
    texture = new sf::Texture( );
}
SpriteSheet::SpriteSheet( int w, int h ): defSprWidth(w), defSprHeight(h)\
, filepath(spriteSheet), texture(nullptr), image( nullptr) {
    texture = new sf::Texture( );
}
SpriteSheet::~SpriteSheet(){ }
bool SpriteSheet::loadResources( ) {
    image = new sf::Image( );
    image->loadFromFile(filepath);
    if(image)
        return true;
    return false;
}
sf::Texture* SpriteSheet::getTile( int x, int y, int w, int h ) {
    sf::IntRect bounds(x,y,w,h);
    if(!image)
        loadResources();
    texture->loadFromImage( *image, bounds );
    return texture;
}


#include <vector>

#include "include/WorldManager.hpp"


//!@DEBUG!
typedef enum tType { water, sand, land};
World::World( ): origin(sf::Vector2f(0,0)), displaymap( sf::Image( )), tex( sf::Texture() )\
, spr(sf::Sprite()), generator( nullptr ), sprSheet( nullptr ) {
    /*
    * SimplexNoise:
    * @< 0.02 :  frequency
    * @< 0.5  :  amplititude
    * @< 2.0  :  Lacunaricity -> direct relation on frecuency increase
    * @< 0.5  :  Persistence  
    *
    * @TODO: Add hmi
    */
    generator = new SimplexNoise(.01f,0.5f, 2.0f,0.4f);
    sprSheet  = new SpriteSheet();
    displaymap.create(W, H, sf::Color::White);

    buildImage( 8 , 0 , 0);
}
World::World(float xOrigin, float yOrigin, float freq, float ampl, float lac, float pers ): \
origin(sf::Vector2f(xOrigin,yOrigin)), displaymap( sf::Image( ))\
, tex( sf::Texture() ), spr(sf::Sprite()), tiledSpr(sf::Sprite()), generator( nullptr )\
, sprSheet( nullptr ) {
    /*
    * SimplexNoise:
    * @< 0.02 :  frequency
    * @< 0.5  :  amplititude
    * @< 2.0  :  Lacunaricity -> direct relation on frecuency increase
    * @< 0.5  :  Persistence  
    *
    * @TODO: Add hmi
    */

    generator = new SimplexNoise(freq, ampl, lac, pers);
    sprSheet  = new SpriteSheet(8,8);

    displaymap.create(W, H, sf::Color::White);

    if(buildImage(8, 0, 0))    printf( "<!>: World MiniMap created!\n" );
    if(updateWorldView(0,0))   printf( "<!>: World created!\n");
}
/*
how da fuck are we goig to make this happen!
*/
World::~World( ) {}
bool World::buildImage(size_t octave, unsigned int shiftX, unsigned int shiftY) {
    for( unsigned int i = 0; i <  W; i++ ){ 
        for( unsigned int j = 0; j <  H; j++ ){
            int tile = 0; 
            float h = generator->fractal(octave,i + shiftX,j + shiftY);
            sf::Color pixelCol( 0 , 0 , 0 , 0);
            if(  h >= -1.0 && h <= -0.4 ){
                pixelCol = sf::Color( 0, 0, 255, 255);
            }else if( h >-0.4 && h <= -0.3 ){
                pixelCol = sf::Color(243, 250, 128, 255);
                tile = 1;
            }else if( h >-0.3 && h <= 0.2 ){
                pixelCol = sf::Color( 0, 128, 0, 255);
                tile = 2;
            }else if( h >0.2 && h <= 0.7 ){
                pixelCol = sf::Color( 0, 196, 0, 255);
                tile = 3;
            }else{
                pixelCol = sf::Color( 81,81,81, 255);
                tile = 4;
            }
            pixelToId[i][j] = tile;
            displaymap.setPixel(i, j, pixelCol);
        }
    }
    tex.loadFromImage(displaymap);
    spr.setTexture( tex , false);
    return false;
}
/*
 *  <@Params:
 *  < mode      -> 0 pixel map, 1 tilemap.
 *  < x , y     -> update world view from available pixelMap.    
 *  < oCx, oCy  -> origin position to draw map , top left;
 *  //<@ MODE 0 ->miniMap;
    //<@ MODE 1 ->spriteMap;
*/
sf::Sprite World::getMapImage(int mode, int x, int y, float oCx, float oCy ) {
    origin = sf::Vector2f( oCy, oCy );
    printf( "|| %d, %d \n", x, y );
    buildImage(8, x, y );
    if( mode == 0)  spr.setPosition( origin );
    else    tiledSpr.setPosition( origin );
    
    if(!updateWorldView( x, y )) return spr;
    return  ( mode == 0) ? spr : tiledSpr ;
}
bool World::updateWorldView( int x, int y) {
    
    int arr[CW][CH];
    if( x < 0 ) x = 0;
    if( y < 0 ) y = 0;
    if( x + CW >= W ) x = W - CW;
    if( y + CH >= H ) y = H - CH;
    for( unsigned int k = 0; k < CW; k++ ) {
        for( unsigned int j = 0; j < CH; j++ ) {
            int g = pixelToId[k+x][j+y];
            arr[k][j] = g;
        }
    }
    pixelsToSpriteImage( arr );
    return true;
}
bool World::pixelsToSpriteImage( int pixels[CW][CH] ) {
    sf::Texture* spriteMap = new sf::Texture( );
    spriteMap->create( CW*8, CH*8);
    for( unsigned int k = 0; k < CW; k++ ){
        for( unsigned int j = 0; j < CH; j++ ){
            int i = pixels[k][j];
            sf::Texture* t;
            switch(i){
                case 0 :
                    t = sprSheet->getTile( 0, 0, 8, 8);
                    break;
                case 1:
                    t = sprSheet->getTile( 8, 0, 8, 8);
                    break;
                case 2:
                    t = sprSheet->getTile( 16, 0, 8, 8);
                    break;
                case 3:
                    t = sprSheet->getTile( 0, 8, 8, 8);
                    break;
                case 4:
                    t = sprSheet->getTile( 8, 8, 8, 8);
                    break;
            }
            spriteMap->update(*t ,k *8 , j*8 );

        }
    }
    tiledSpr.setTexture( *spriteMap );
    return true;
}

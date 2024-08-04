#include <vector>

#include "include/WorldManager.hpp"

//!@DEBUG!
typedef enum tType { water, sand, land};
World::World( SpriteSheet * sprS): origin(sf::Vector2f(0,0)), displaymap( sf::Image( )), tex( sf::Texture() )\
, spr(sf::Sprite()), generator( nullptr ), sprSheet( sprS ) {
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
    displaymap.create(W, H, sf::Color::White);

    buildImage( 8 , 0 , 0, 0);
}
World::World(float xOrigin, float yOrigin, float freq, float ampl, float lac, float pers , SpriteSheet* sprS): \
origin(sf::Vector2f(xOrigin,yOrigin)), displaymap( sf::Image( ))\
, tex( sf::Texture() ), spr(sf::Sprite()), generator( nullptr )\
, sprSheet( sprS ) {
    transform = sf::Transformable();
    /*
    * SimplexNoise:
    * @< 0.02 :  frequency
    * @< 0.5  :  amplititude
    * @< 2.0  :  Lacunaricity -> direct relation on frecuency increase
    * @< 0.5  :  Persistence  
    *
    * @TODO: Add hmi
    */
    transform.setPosition(origin);
    generator = new SimplexNoise(freq, ampl, lac, pers);
    displaymap.create(W, H, sf::Color::White);

    if(buildImage(8, 0, 0, 0))    printf( "<!>: World MiniMap created!\n" );
    if(updateWorldView(0,0))   printf( "<!>: World created!\n");
}
/*
how da fuck are we going to make this happen! Some~o~How
*/
World::~World( ) {}
bool World::buildImage(size_t octave, unsigned int shiftX, unsigned int shiftY, unsigned int type ) {
    pixelToId = std::vector<std::vector<int>>(W, std::vector<int>(H,0));
    for( unsigned int i = 0; i <  W; i++ ){
        for( unsigned int j = 0; j <  H; j++ ){
            int tile = 0; //Representing tile position on spritesheet  0 = default_water; 18 = default grass 23 = dirt: 
            
            float h = generator->fractal(octave,i + shiftX,j + shiftY);
            sf::Color pixelCol(0, 196, 0, 255);
            //Plane map
            if( type == 0 ){
                tile = 18;
            }else{
                if(  h >= -1.0 && h <= -0.4 ){
                    pixelCol = sf::Color( 0, 0, 255, 255);
                }else if( h >-0.4 && h <= -0.3 ){
                    pixelCol = sf::Color(0, 0, 255, 255);
                    tile = 18;
                }else if( h >-0.3 && h <= 0.0 ){
                    pixelCol = sf::Color( 0, 128, 0, 255);
                    tile = 18;
                }else if( h >0.0 && h <= 0.5 ){
                    pixelCol = sf::Color( 0, 196, 0, 255);
                    tile = 23;
                }else if( h > 0.5  ){
                    pixelCol = sf::Color( 0, 255, 0, 255);
                    tile = 28;
                }
            }
            pixelToId[i][j] = tile;
            displaymap.setPixel(i, j, pixelCol);

        }
    }
    displaymap.setPixel(W/2,H/2, sf::Color::Red);
    tex.loadFromImage(displaymap);
    spr.setTexture( tex , false);
    spr.setPosition( origin );
    return false;
}
/*
 *  <@Params:
 *  < x , y     -> update world view from available pixelMap.    
 *  < oCx, oCy  -> origin position to draw map , top left;

*/
bool World::getMapImage( int x, int y, float oCx, float oCy ) {
    origin = sf::Vector2f( oCy, oCy );
    transform.setPosition(x - ((CW* 8) / 2),y - ( (CH * 8)  / 2));
    buildImage(8, x, y , 0);
    updateWorldView(x,y);
    //spr.setPosition(origin);
    return true;
}
bool World::updateWorldView( int x, int y) {
    
    std::vector<std::vector<int>> arr(CW, std::vector<int>(CH, 0));
    if( x < 0 ) x = 0;
    if( y < 0 ) y = 0;
    if( x + CW >= W ) x = W - CW;
    if( y + CH >= H ) y = H - CH;
    for( unsigned int k = 0; k < CW; k++ ) {
        for( unsigned int j = 0; j < CH; j++ ) {
            std::copy( pixelToId[k+x].begin(), pixelToId[k+x].begin() + CH, arr[k].begin() );
        }
    }
    sprSheet->setTileMap(arr);
    if(!pixelsToSpriteImage( arr )) return false;
    return true;
}
std::vector<int> World::getTile( int x, int y, Collider other ){
    std::vector<Tile*> ts;
    std::vector<int> corners = sprSheet->getnearestTiles( x, y, ts);
    int h = 0;
    for( auto& c: corners ){
        if( c >  23 && ts[h]->hasColl()){
            
        }
        h++;
    
    }
    return corners;
}
bool World::pixelsToSpriteImage( std::vector<std::vector<int>> pixels ) {
    sprSheet->update( pixels, CW, CH);
    if(!sprSheet){
        printf( "\n\n\nNo spriteSheet\n\n\n"  );
        return false;
    }
    return true;
}
int c = 0;
void World::drawmap( sf::RenderTarget* target, sf::RenderStates states) {
    if(c == 0)  displaymap.saveToFile( "MapGeneration.bmp" );
    //states.transform = transform.getTransform();
    states.texture = sprSheet->getTexture();
    target->draw(sprSheet->getTiles(), states);
    //target->draw(spr); 
}


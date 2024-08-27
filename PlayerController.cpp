#include "include/PlayerController.hpp"
#include <SFML/Graphics/VertexBuffer.hpp>

/*
    DIRECTIONS
    L -> -1 , 0
    U ->  0 , 1
    R ->  1 , 0
    D ->  0 ,-1
*/
PlayerController::PlayerController( ): Object( 0, sf::Vector2f( 20 , 20) , sf::Vector2f( 8, 8), false, std::vector<sf::VertexArray>(), -1 , nullptr), lookingDir(sf::Vector2f(0, -1)), acceleration(sf::Vector2f(0,0)), velocity(sf::Vector2f(0,0)) {
    set_FillColor( pColor );
    vA = sf::VertexArray(sf::Lines, 8 );
}
PlayerController::PlayerController(sf::Vector2f pos , sf::Vector2f dim, std::vector<sf::VertexArray> vtx, sf::Texture* s, unsigned int ind , bool hAnim , unsigned int animSz ): Object(0, pos , dim , true, vtx, (int)ind, s, hAnim , animSz), lookingDir(sf::Vector2f(0, -1)),acceleration(sf::Vector2f(0,0)), velocity(sf::Vector2f(0,0)) {
    vA = sf::VertexArray(sf::Lines, 8 );
    printf( "pos at entities: %f, %f\n", pos.x, pos.y );
}
PlayerController::~PlayerController(){

}
//пись мо домой :)
void PlayerController::ColisionMovementUpdate( ){
    // 0 2 4 6 8
    // 0 1 2 3 4
    int c = 0;
    //  1 3 5 7
    sf::Vector2f p = get_position();
    for( int i = 1; i < 8; i+=2, c++ ){
        if( c == 0 && nearTiles[i] > 18 ){
            vA[0].position = sf::Vector2f( p.x  , p.y );
            vA[0].color = sf::Color(255,0,0,255);
            vA[1].position = sf::Vector2f( p.x  , p.y - 8 );
            vA[1].color = sf::Color(0,0,255,255);
            acceleration.x = 0;
            acceleration.y =  accel/2; 
            //velocity.y = 0 ;
        }
        if( c == 3 && nearTiles[i] > 18 ){
            vA[6].position = sf::Vector2f( p.x  , p.y );
            vA[6].color = sf::Color(255,0,0,255);
            vA[7].position = sf::Vector2f( p.x  , p.y + 8 );
            vA[7].color = sf::Color(0,0,255,255);
            acceleration.x = 0;
            acceleration.y = -accel/2; 
            //velocity.y = 0;
        }
        if( c == 1 && nearTiles[i] > 18 ){
            vA[2].position = sf::Vector2f( p.x  , p.y );
            vA[2].color = sf::Color(255,0,0,255);
            vA[3].position = sf::Vector2f( p.x - 8 , p.y );
            vA[3].color = sf::Color(0,0,255,255);
            acceleration.y = 0;
            acceleration.x = accel/2; 
            //velocity.x = 0;
        }
        if( c == 2 && nearTiles[i] > 18 ){
            vA[4].position = sf::Vector2f( p.x  , p.y );
            vA[4].color = sf::Color(255,0,0,255);
            vA[5].position = sf::Vector2f( p.x  + 8, p.y );
            vA[5].color = sf::Color(0,0,255,255);
            acceleration.y = 0;
            acceleration.x = -accel/2; 
            //velocity.x = 0 ;
        }
    }
}
void PlayerController::update( float dt ) {
    sf::Vector2f v;
    //Check if collisions against near tiles; ( debug : checking if 1 or more colisions detected)
    /*
    if( nearTiles.size() > 0 ){
        ColisionMovementUpdate();
    }
    */
    set_move(velocity.x * dt, velocity.y * dt);
    collider->SetVertexAxis(get_position(), sf::Vector2f(4,4));
    velocity = acceleration ;
}
void PlayerController::handleEvents( sf::Event e ) {
    //int speed = 10 ;
    if (e.type == sf::Event::KeyPressed){
        if (e.key.code == sf::Keyboard::Left){
            acceleration.x = -accel;
            lookingDir.x = 1;
            setCurrentTexture( 1 );
        }
        else if (e.key.code == sf::Keyboard::Right){
            acceleration.x = accel;
            lookingDir.x = -1;
            setCurrentTexture( 0 );
        }
        else if (e.key.code == sf::Keyboard::Up){
            acceleration.y =- accel;
            lookingDir.y = 1;
            setCurrentTexture( 3 );
        }
        else if (e.key.code == sf::Keyboard::Down){
            acceleration.y = accel;
            lookingDir.y =  -1;
            setCurrentTexture( 2 );
        }else if (e.key.code == sf::Keyboard::P){
            accel += 0.10f;
        }else if (e.key.code == sf::Keyboard::O){
            accel -= 0.10f;
        }
    }else if (e.type == sf::Event::KeyReleased){
        if (e.key.code == sf::Keyboard::Left){
            acceleration.x = 0;
            lookingDir = sf::Vector2f(0,0);
        }else if( e.key.code == sf::Keyboard::Right ){
            acceleration.x = 0;
            lookingDir = sf::Vector2f(0,0);
        }
        if (e.key.code == sf::Keyboard::Up){
            acceleration.y = 0 ;
            lookingDir = sf::Vector2f(0,0);
        }else if( e.key.code == sf::Keyboard::Down ){
            acceleration.y = 0;
            lookingDir = sf::Vector2f(0,0);
        }
    }
    velocity = acceleration ;
}
void PlayerController::updateNearTile( std::vector<int> t ){
    nearTiles = t;
}
float PlayerController::getPlayerAccel(){
    return accel;
}
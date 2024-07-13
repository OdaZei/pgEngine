#include "include/PlayerController.hpp"


/*
    DIRECTIONS
    L -> -1 , 0
    U ->  0 , 1
    R ->  1 , 0
    D ->  0 ,-1
*/
PlayerController::PlayerController( ): Object( 0, sf::Vector2f( 20 , 20) , sf::Vector2f( 8, 8)), lookingDir(sf::Vector2f(0, -1)), velocity(sf::Vector2f()) {
    set_FillColor( pColor );

}
PlayerController::PlayerController(sf::Vector2f pos , sf::Vector2f dim): Object(0, pos , dim ), lookingDir(sf::Vector2f(0, -1)), velocity(sf::Vector2f()) {
    Transform(pos, dim);
    set_FillColor( pColor );
    shape->setPosition(pos.x, pos.y);
}
PlayerController::~PlayerController(){

}
void PlayerController::update( float dt ) {
    sf::Vector2f v;
    set_move(velocity.x * dt, velocity.y * dt);
    v = get_position();
    collider->SetVertexAxis(v , Transform::get_dimension() );
    
    //collider->setOrigin( v.x, v.y );
    printf( "Object Pos: x: %f, y: %f\n", collider->getPosition().x, collider->getPosition().y );
}
void PlayerController::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    states.transform *= Transform::getTransform();
    //@Check: Collider axis states offset's the coordinates!;
    target.draw( collider->colliderAxis );
	target.draw( *shape, states );
}
void PlayerController::handleEvents( sf::Event e ) {
    int speed = 10 ;
    if (e.type == sf::Event::KeyPressed){
        if (e.key.code == sf::Keyboard::Left){
            velocity.x = -speed;
            lookingDir.x = 1;
        }
        else if (e.key.code == sf::Keyboard::Right){
            velocity.x = speed;
            lookingDir.x = -1;
        }
        else if (e.key.code == sf::Keyboard::Up){
            velocity.y = -speed;
            lookingDir.y = 1;
        }
        else if (e.key.code == sf::Keyboard::Down){
            velocity.y = speed;
            lookingDir.y =  -1;
        }
    }else if (e.type == sf::Event::KeyReleased){
        if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right){
            velocity.x = 0;
            lookingDir = sf::Vector2f(0,0);
        }
        else if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Down){
            velocity.y = 0;
            lookingDir = sf::Vector2f(0,0);
        }
    }
}

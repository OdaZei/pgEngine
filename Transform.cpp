#include "include/Transform.hpp"
#include <cstdio>

Transform::Transform( ): Transformable(), position( sf::Vector2f(0,0) ), dimensions( sf::Vector2f(0,0) ) {}

Transform::Transform( sf::Vector2f pos, sf::Vector2f dim ): Transformable(), position( pos ), dimensions( dim ) {
	printf("Setting transform position at: %f, %f, %f, %f\n", position.x, position.y, dim.x, dim.y);
}

Transform::~Transform( ) { }
void Transform::Move(float x, float y) {
	move(x,y);
	position.x += x;
	position.y += y;
	printf( "Transform Position: X: %f, Y: %f\n", position.x, position.y );
}

sf::Vector2f Transform::get_position(){
	return position;
}
sf::Vector2f Transform::get_dimension(){
	return dimensions;
}
void Transform::set_position( sf::Vector2f pos ){
	position = pos;
}
void Transform::set_dimensions(sf::Vector2f dim ){
	dimensions = dim;
}
sf::Transform Transform::getTransf( ) const {
	return getTransform();
}
#include "include/Object.hpp"
#include <cstdio>
Object::Object(): oData(nullptr), shape(nullptr) {
	Transform();
	Node();
	shape = new sf::RectangleShape( );
	oData = new ObjectData(-1, false, false );
	collider = new Collider();
}
Object::Object( int type, sf::Vector2f pos, sf::Vector2f dim ): oData(nullptr)\
, shape(nullptr), collider(nullptr) {
	Transform( pos, dim );
	Transform::setPosition( pos );
	Node(); // Creates Drawable node;
	shape = new sf::RectangleShape( );
	shape->setPosition( pos );
	shape->setSize( dim );
	shape->setOrigin( pos.x + dim.x / 2 , pos.y + dim.y / 2);
	//set has collider and canMove
	if(type != 0 ){
		oData = new ObjectData(type, true, false );
	}else{
		oData = new ObjectData(type, true, true );
	}
	collider = new Collider( pos, dim );

}
Object::~Object(){}
void Object::set_move( float x, float y ){
	Move( x, y );
	collider->Move(x,y);
}
void Object::set_position( float x, float y ) {
	Transform::setPosition( x, y );
	shape->setPosition( x, y );
	collider->setPosition( x, y);
}
void Object::set_rotation( int angle ) {
	setRotation( float(angle) );
	sf::Transform transform = shape->getTransform();
	transform.rotate( angle );
}
sf::Vector2f Object::get_position() {
	return getPosition( );
}
void Object::set_FillColor( sf::Color c ) {
	shape->setFillColor( c );
}
sf::RectangleShape Object::getShape( ) {
	return *shape;
}
void Object::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const{
	states.transform *= getTransform();
	target.draw( collider->colliderAxis , states );
	target.draw( *shape , states );
}
void Object::update( float dt )  {
	
}
void Object::handleEvents( sf::Event e) {
}
/*
void Object::setObjectType( int t ) {
	type = t;
}
*/

int Object::getObjectType( ) {
	return oData->type;
}

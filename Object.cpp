#include "include/Object.hpp"
#include <cstdio>
Object::Object(): oData(nullptr), shape(nullptr) {
	Transform();
	Node();
	shape = new sf::RectangleShape( );
	oData = new ObjectData(-1, false, false );

	collider 	= new Collider();
	HasTexture 	= false;
	
	spritesheetTexture  = nullptr;
	hasAnimation 		= false;
	nTextures			= 0;
	currentTexture		= 0;

}
/*
	(  0 ) hasTexture -> true && textureIndex > -1;
	( *0 ) need reference to vertexBuffer index;
	** _vArr -> is passed as default
*/
Object::Object( int type, sf::Vector2f pos, sf::Vector2f dim , bool _hasTexture, sf::VertexArray _vArr, int _textureIndex, sf::Texture* s, ): shape(nullptr), collider(nullptr),oData(nullptr) {
	Transform( pos, dim );
	Transform::setPosition( pos );
	Node(); // Creates Drawable node;
	// Case static texture;
	if( _hasTexture && _textureIndex > -1 ) {
		vertexArr  = _vArr;
		hasTexture =  _hasTexture;
		textureVertexIndex = _textureIndex;
		spritesheetTexture = s;
		if()
	}else {
		//Case no Texture;
		hasTexture = false;
		shape = new sf::RectangleShape( );
		shape->setPosition( pos );
		shape->setSize( dim );
		shape->setOrigin( pos.x + dim.x / 2 , pos.y + dim.y / 2);
	}
	//set has collider and canMove
	if(type != 0 ){
		oData = new ObjectData(type, false, false );
	}else{
		oData = new ObjectData(type, true, true );
	}
	collider = new Collider( pos, dim );
}
Object::~Object(){}
void Object::set_move( float x, float y ){
	Move( x, y );
	collider->Move(x,y);
	if( hasTexture ){
		for( int i = 0 ; i < vertexArr.getVertexCount(); i++ ) {
			sf::Vertex* v = &vertexArr[i];
			v->position.x += x;
			v->position.y += y;
		}
	}
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
	printf( "Running Object Draw\n" );
	target.draw( collider->colliderAxis , states );
	if( hasTexture ){
		states.texture = spritesheetTexture;
		target.draw( vertexArr, states);
	}else
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
Collider* Object::getCollider() {
	return collider;
}

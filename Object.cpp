#include "include/Object.hpp"
#include <cstdio>

/*
	Object ( ) : PARAMS :
		TYPE( INT ) : OBJECT TYPE, DEFINED ON ENTITYMANAGER, STORING FOR FUTURE USE;
			MODIFY TO UNSIGNED INT, CASE NEGATIVE TYPE IS SET;
		POS ( SF:VECTOR2F )  : DEFINING OBJECT STARTING POSITION.
		DIM ( SF::VECTOR2F ) : DEFINING OBJECT DIMENSIONS( WORLD UNITS ; MAYBE 16 BITS  = 1 WORLD UNIT );
*/

Object::Object(): oData(nullptr), shape(nullptr) {
	//Transform();
	Node();
	shape = new sf::RectangleShape( );
	oData = new ObjectData();

	collider 	= new Collider();
	spritesheetTexture  = nullptr;
	currentTexture		= 0;
	vertexArr 			= std::vector<sf::VertexArray>();
}
/*
	(  0 ) hasTexture -> true && textureIndex > -1;
	( *0 ) need reference to vertexBuffer index;
	** _vArr -> is passed as default
*/
Object::Object( int type, sf::Vector2f pos, sf::Vector2f dim , bool _hasTexture, std::vector<sf::VertexArray> _vArr, int _textureIndex, sf::Texture* s, bool hasTxs, unsigned int nTxs): shape(nullptr), collider(nullptr),oData(nullptr) {
	//Transform( pos, dim );
	Node(); // Creates Drawable node;
	// Case static texture;
	if( _hasTexture && _textureIndex > -1 ) {
		vertexArr  = _vArr;
		textureVertexIndex = _textureIndex;
		spritesheetTexture = s;
		if( hasTxs ){
			if( nTxs > 0 ){
				//Start animation from index 0;
				currentTexture = 0; 
			}else{
				//Set static textures if nTxs( number of textures ) == 0;
				hasTxs = false;
				nTxs = 0;
				currentTexture = 0;
			}
		}
	}else {
		//Case no Texture;
		_hasTexture = false;
		hasTxs 		= false;
		nTxs   		= 0;
		shape = new sf::RectangleShape( );
		shape->setPosition( pos );
		shape->setSize( dim );
		shape->setOrigin( pos.x + dim.x / 2 , pos.y + dim.y / 2);
	}
	//set has collider and canMove
	if(type != 0 ){
		oData = new ObjectData(type, true, false, _hasTexture, hasTxs, nTxs );
	}else{
		oData = new ObjectData(type, true, true , _hasTexture, hasTxs, nTxs );
	}
	if(oData->has_collider)
		collider = new Collider( pos, dim );
}
Object::~Object(){}
void Object::set_move( float x, float y ){
	if( oData->can_move )
		Move( x, y );
}
void Object::set_position( float x, float y ) {
	setPosition( x, y );
	if(!oData->has_texture)
		shape->setPosition( x, y );
	
	
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
unsigned int ct = 0;
void Object::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const{
	
	states.transform *= getTransf();
	
	if( oData->has_texture ){
		states.texture = spritesheetTexture;
		if( oData->has_animation ){
			target.draw( vertexArr[currentTexture] , states );
		}else{
			target.draw( vertexArr[currentTexture], states );	
		}
	}else{
		target.draw( *shape , states );
	}
	target.draw( collider->colliderAxis );
}
void Object::update( float dt )  {}
void Object::handleEvents( sf::Event e) {
}
void Object::setCurrentTexture( unsigned int u ){
	if( checkAnimationPreset( u ) )
		currentTexture = u;
}
bool Object::checkAnimationPreset( unsigned int u ){
	return ( oData->has_animation && ( u < oData->num_textures ));
}
int Object::getObjectType( ) {
	return oData->type;
}
Collider* Object::getCollider() {
	return collider;
}

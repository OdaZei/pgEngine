#pragma once

#include "Transform.hpp"
#include "Node.hpp"
#include "Collider.hpp"
#include "ObjectData.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

class Object : public Node, public Transform {
	public:
		Object( );
		Object(int type, sf::Vector2f pos, sf::Vector2f dim );
		~Object( );
		
		void set_move( float x, float y );
  		void set_position( float x, float y );
		void set_rotation( int angle ); 
		
		sf::Vector2f get_position();
		
		void set_FillColor( sf::Color c );
  		
		sf::RectangleShape getShape( );
		
		virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const override ;
		virtual void update( float dt );
		virtual void handleEvents( sf::Event e);

		//void setObjectType( int t );
		int getObjectType();

		ObjectData* 		oData;
		sf::RectangleShape* shape;
		Collider* 			collider;
};
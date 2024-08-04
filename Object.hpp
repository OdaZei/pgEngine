#pragma once

#include "Transform.hpp"
#include "Node.hpp"
#include "Collider.hpp"
#include "ObjectData.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>

class Object : public Node, public Transform {
	public:
		
		ObjectData* 		oData;

		Object( );
		Object(int type, sf::Vector2f pos , sf::Vector2f dim , bool _hasTexture ,  std::vector<sf::VertexArray> _vArr , int _textureIndex = -1 , sf::Texture* s = nullptr, bool hasTxs = false , unsigned int nTxs = 0);
		~Object( );
		
		void set_move( float x, float y );
  		void set_position( float x, float y );
		void set_rotation( int angle ); 
		
		sf::Vector2f get_position();
		
		void set_FillColor( sf::Color c );
  		
		sf::RectangleShape getShape( );
		
		void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const override;
		virtual void update( float dt );
		virtual void handleEvents( sf::Event e);

		//void setObjectType( int t );
		
		int getObjectType();

		Collider* getCollider();

		Collider* 			collider;
		
	protected:
		sf::RectangleShape* shape;
		
		bool 				hasTexture;

		unsigned int 		textureVertexIndex;

		std::vector<sf::VertexArray> 	vertexArr;

		sf::Texture* 		spritesheetTexture;
		
		bool 				hasAnimation;
		unsigned int		nTextures;
		mutable int 				currentTexture;
};
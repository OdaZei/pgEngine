#pragma once

#include "Geometry.hpp"
#include <SFML/Graphics/Transformable.hpp>

class Transform : public sf::Transformable{
	public:
		Transform( );
		Transform( sf::Vector2f pos, sf::Vector2f dim );
		
		~Transform();
		
		sf::Transform getTransf( ) const;
		void Move(float , float );
		
		sf::Vector2f get_position();
		sf::Vector2f get_dimension();

		void set_position(sf::Vector2f pos);
		void set_dimensions( sf::Vector2f dim);
	protected:
		sf::Vector2f position;
		sf::Vector2f dimensions;
};
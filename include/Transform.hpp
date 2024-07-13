#pragma once

#include "Geometry.hpp"
#include <SFML/Graphics/Transformable.hpp>

class Transform : public sf::Transformable{
	public:
		typedef sf::Vector2f v;
		Transform();
		Transform( sf::Vector2f pos, sf::Vector2f dim );
		~Transform();
		void Move(float x, float y);
		sf::Vector2f get_position();
		sf::Vector2f get_dimension();
		void set_position(v pos);
		void set_dimensions(v dim);
	protected:
		sf::Vector2f position;
		sf::Vector2f dimensions;
};
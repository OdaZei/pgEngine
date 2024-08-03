#pragma once

#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Node : public sf::Drawable{
	public:
		Node();
		~Node();
		
		void 		AttachChild( Node* child );
		Node* 		DetachChild( const Node* child );

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		
		std::vector<Node*> Children;
		Node* Parent;
};
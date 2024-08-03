#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include "Transform.hpp"

class Collider: public Transform {
    public:
        Collider();
        Collider( sf::Vector2f pos , sf::Vector2f dim );
        ~Collider();

        void SetVertexAxis( sf::Vector2f pos, sf::Vector2f dim ); //Draw vertex boundaries

        //returns true if an intersection between 2 lines exist, ixOut, iyOut intersection point;
        bool IntersectionBetweenLines( sf::Vector2f A_p1, sf::Vector2f A_p2, sf::Vector2f B_p1, sf::Vector2f B_p2 , float& ixOut, float& iyOut);
        bool CheckCollision( Collider& other );

        sf::VertexArray colliderAxis;

};

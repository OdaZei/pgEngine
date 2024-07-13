#pragma once

#include <SFML/System/Vector2.hpp>
class Grid {
    public:
    Grid();
    ~Grid(){ };
    sf::Vector2f pointToAngleTransformation( sf::Vector2f point, float angle );

    static sf::Vector2f pointToPointDistance( sf::Vector2f p1, sf::Vector2f p2);
};
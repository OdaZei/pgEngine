#include <cstdio>
#include <math.h>
#include "include/Grid.hpp"

static double dMat[4];
static float radCte = 0.01745329; // pi * 180 * angle -> to radians
Grid::Grid(){

}
sf::Vector2f Grid::pointToAngleTransformation( sf::Vector2f point, float angle ) {
    dMat[0] = cos(radCte*angle);
    dMat[3] = cos(radCte*angle);
    dMat[1] = -sin(radCte*angle);
    dMat[2] = sin(radCte*angle);
    //Need an origing vector to rotate over
    sf::Vector2f result, origin = sf::Vector2f(50 , -5 );

    double tw = point.x + origin.x;
    double tq = point.y + origin.y;

    result.x = dMat[0] * tw + dMat[1] * tq + origin.x;
    result.y = dMat[2] * tw + dMat[3] * tq + origin.y;
    return result;
}

sf::Vector2f Grid::pointToPointDistance( sf::Vector2f p1, sf::Vector2f p2){
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;

    return sf::Vector2f(dx , dy );
}
/*
   p1
       p2
   0.   
   rotating p1 to p2 over originbg point o
*/
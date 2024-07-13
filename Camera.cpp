#include "include/Camera.hpp"
#include "include/Grid.hpp"

#include <SFML/Graphics/Rect.hpp>
//viewSizeX -> 680 / 8; viewSizeY -> 480 / 8;
Camera::Camera(): xCoord(0), yCoord(0), viewSizeX(170)\
                , viewSizeY(120), viewPort( sf::View() ) {
    //
}
Camera::Camera(float x, float y, float w, float h):xCoord(0)\
, yCoord(0), viewSizeX(w), viewSizeY(h), viewPort( sf::View() ) {
    viewPort.reset( sf::FloatRect(xCoord, yCoord, viewSizeX, viewSizeY ) );
}
Camera::~Camera() {
    //
}
void Camera::moveCamera( float x, float y , float dt) {
    sf::Vector2f p( x, y );
    sf::Vector2f dist = Grid::pointToPointDistance( p, viewPort.getCenter() );
    if(dist.x * dist.x + dist.y * dist.y > 100)
        viewPort.move( dist.x * dt, dist.y*dt );
}
sf::Vector2f Camera::getViewSize( ) {
    return sf::Vector2f( viewSizeX, viewSizeY );
}
sf::Vector2f Camera::getViewPosition( ) {
    return sf::Vector2f( xCoord, yCoord );
}
sf::View Camera::getCamera( ) {
    return viewPort;
}
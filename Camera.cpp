#include "include/Camera.hpp"
#include "include/Grid.hpp"

#include <SFML/Graphics/Rect.hpp>
//viewSizeX -> 680 / 8; viewSizeY -> 480 / 8;
Camera::Camera(): xCoord(0), yCoord(0), viewSizeX(170)\
                , viewSizeY(120), viewPort( sf::View() )\
                , clip(false), xCCoord(0), yCCoord(0) \
                , clipSizeX(0), clipSizeY(0) {
    //
}
Camera::Camera(float x, float y, float w, float h, bool c, float cX, float cY, float cW, float cH):xCoord(0)\
, yCoord(0), viewSizeX(w), viewSizeY(h), viewPort( sf::View() )\
, clip(c), xCCoord(cX), yCCoord(cY), clipSizeX(cW), clipSizeY(cH) {
    viewPort.reset( sf::FloatRect(xCoord, yCoord, viewSizeX, viewSizeY ) );
}
Camera::~Camera() {
    //
}
bool Camera::Clip(float x, float y) {
    //Top-Left coord; 
    float difX, difY = .0f;
    difX = xCCoord - x;
    difY = ( yCCoord + clipSizeY / 2) - y;
    if(difX <= (clipSizeX / 2) || difY <= (clipSizeY / 2))
        return false;
    return true;

}
void Camera::moveCamera( float x, float y, float dt) {
    if( clip && Clip( x, y ))   return;
    sf::Vector2f p( x, y );
    sf::Vector2f dist = Grid::pointToPointDistance( p, viewPort.getCenter() );
    if(dist.x * dist.x + dist.y * dist.y > 50)
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
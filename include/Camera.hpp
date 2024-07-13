#pragma once

#include <SFML/Graphics/View.hpp>

class Camera {
    public:
        Camera();
        Camera(float x, float y, float w, float h);
        ~Camera();

        void moveCamera(float x, float y, float dt);
        sf::Vector2f getViewSize( );
        sf::Vector2f getViewPosition();
        sf::View getCamera();
    protected:
        float xCoord;
        float yCoord;
        float viewSizeX;
        float viewSizeY;

        sf::View viewPort;
};

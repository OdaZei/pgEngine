#pragma once

#include <SFML/Graphics/View.hpp>

class Camera {
    public:
        Camera();
        Camera(float x, float y, float w, float h, bool c, float cX, float cY, float cW, float cH);
        ~Camera();
        bool Clip( float x, float y );
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

        bool clip;          // Is the camera clipped
        float xCCoord;      //Clip x pos;
        float yCCoord;      //Clip y pos;
        float clipSizeX;
        float clipSizeY;

};

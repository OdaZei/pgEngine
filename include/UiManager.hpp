#pragma once

#include <vector>
#include <memory>

#include "Camera.hpp"
#include "UIElement.hpp"

class UiManager{
    public:
        UiManager();
        UiManager(unsigned int);
        UiManager(int, int, int, int);
        ~UiManager();
        int addTextElement(const char *, int, int);

        //<@Debug
        int addMenu( int x, int y );
        
        UiElement* popElement( unsigned int);
        void update(unsigned int,float);
        void update(unsigned int index, char arr[32]);
        void render(sf::RenderTarget& target, sf::RenderStates states); 

        sf::View getCamera();
    private:
        Camera * uiCam;
        std::vector<std::shared_ptr<UiElement*>> elements;
};  
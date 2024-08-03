#pragma once

#include <vector>
#include <memory>

#include "Camera.hpp"
#include "UIElement.hpp"
#include "Menu.hpp"

class UiManager{
    public:
        UiManager();
        UiManager(unsigned int);
        UiManager(int, int, int, int);
        ~UiManager();
        int addTextElement(const char *, int, int);

        //<@Debug
        int addMenu( int x, int y , char[32]);
        int addMenu( std::shared_ptr<Menu> menu );
        UiElement popElement( unsigned int);
        //updates text with float
        void updateF(unsigned int,float);
        //Updates menu index text with chars
        void updateC(unsigned int index, char arr[32]);
        //Updates text with chars
        void updateTC(unsigned int index, char arr[32]);
        void render(sf::RenderTarget& target, sf::RenderStates states); 

        sf::View getCamera();
    private:
        Camera * uiCam;
        std::vector<std::shared_ptr<TextHolder>> elements;
        std::shared_ptr<Menu>  menu;
};  
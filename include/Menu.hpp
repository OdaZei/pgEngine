#pragma once

#include "TextHolder.hpp"
#include <vector>
#include <memory>

typedef struct menudata {
    menudata();
    menudata(int, int, int, char[32]);
    ~menudata();
    int ind, xPos , yPos;
    char data[32];
}menudata;

class Menu: public UiElement {
    public:
        Menu();
        Menu( const UiElement& );
        ~Menu();
        void addData( int, int, char[32]);
        void overrideData(int , char[32] );
        virtual void update( float dt) const override;
        virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const override;
        int dataFSize();
    private:
        std::vector<std::shared_ptr<menudata>> mData;
        std::vector<std::shared_ptr<TextHolder>> mElm;
};
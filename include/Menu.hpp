#pragma once

#include "TextHolder.hpp"
#include <vector>
#include <memory>

struct menudata {
    menudata(int, int, int, char[32]);
    ~menudata();
    int ind, xPos , yPos;
    char data[32];
};

class Menu: public UiElement {
    public:
        Menu();
        ~Menu();
        void addData( int, int, char[32]);
        void overrideData(int , char[32] );
        virtual void update( float dt) const override;
        virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const override;
    private:
        std::vector<menudata*> mData;
        std::vector<std::shared_ptr<TextHolder*>> mElm;
};
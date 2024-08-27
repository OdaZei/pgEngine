#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class UiElement{
    public:
        UiElement(unsigned int, int x, int y);
        ~UiElement();
        void setIndex(unsigned int);
        virtual unsigned int getType();
        //virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update(float) const ;
        virtual void drawCurrent (sf::RenderTarget& target, sf::RenderStates states) const;
        int           xPos;
        int           yPos;
    protected:
        unsigned int  index;
        unsigned int  type;
        //const char* name;

};
#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class UiElement{
    public:
        UiElement();
        ~UiElement();
        void setIndex(unsigned int);
        //virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update(float) const ;
        virtual void drawCurrent (sf::RenderTarget& target, sf::RenderStates states) const;
    protected:
        unsigned int index;
        //const char* name;

};
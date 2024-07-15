#pragma once

#include <SFML/Graphics/Text.hpp>

#include "UIElement.hpp"

class TextHolder: public UiElement{
    public:
        TextHolder( const char * st, unsigned int textSize, int x, int y);
        ~TextHolder();

        void setText( char * st, unsigned int textSize) ;
        void floatToString( float f, char * s ) const;
        virtual void update( float dt ) const override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    protected:
        int              xPos;
        int              yPos;
        const char *     textfield;
        sf::Font   *     textfont;
        sf::Text   *     textObj;
};
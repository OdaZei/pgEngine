#pragma once

#include <SFML/Graphics/Text.hpp>

#include "UIElement.hpp"

class TextHolder: public UiElement{
    public:
        TextHolder();
        TextHolder( const char * st, unsigned int textSize, int x, int y);
        TextHolder( const UiElement& e);
        ~TextHolder();

        void setText( char st[32], unsigned int textSize) ;
        void floatToString( float f, char * s ) const;
        virtual void update( float dt ) const override;
        void updateC ( char arr[32] );
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        const sf::String getText();
    protected:
        const char *     textfield;
        sf::Font   *     textfont;
        sf::Text   *     textObj;
};
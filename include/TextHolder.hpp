#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Node.hpp"

class TextHolder: public Node{
    public:
        TextHolder(const char * st, int x, int y);
        ~TextHolder();

        void setText( const char * st);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    protected:
        int              xPos;
        int              yPos;
        const char *     textfield;
        sf::Font   *     textfont;
        sf::Text   *     textObj;
};
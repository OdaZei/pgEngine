#include "include/TextHolder.hpp"
#include "include/filepaths.hpp"

TextHolder::TextHolder( const char * st, int x, int y ): xPos(x), yPos(y), textfield(st), textfont(nullptr) {
    textfont = new sf::Font();
    textfont->loadFromFile(fontpath);
    textObj = new sf::Text( sf::String(" ") , *textfont, 12);
    textObj->setStyle(sf::Text::Bold);
    textObj->setFillColor(sf::Color::White);
    textObj->setPosition(x,y);
}
TextHolder::~TextHolder(){}
void TextHolder::setText( const char * st) {
    if(textObj)
        textObj->setString( st );
    else{
        if(textfont)
            textObj = new sf::Text( st, *textfont, 12 );
        else{
            textfont = new sf::Font();
            textfont->loadFromFile(fontpath);
            textObj  = new sf::Text( st, *textfont, 12 );
        }
    }
}
void TextHolder::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= textObj->getTransform();
	target.draw( *textObj , states );
}
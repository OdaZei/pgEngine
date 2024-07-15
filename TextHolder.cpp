#include "include/TextHolder.hpp"
#include "include/filepaths.hpp"

#include <cstring>

TextHolder::TextHolder(  const char * st, unsigned int textSize, int x, int y ): xPos(x), yPos(y), textfield(st), textfont(nullptr) {
    UiElement();
    textfont = new sf::Font();
    textfont->loadFromFile(fontpath);
    textObj = new sf::Text( sf::String(textfield) , *textfont, textSize);
    textObj->setStyle(sf::Text::Bold);
    textObj->setFillColor(sf::Color::White);
    textObj->setPosition((int)xPos,(int)yPos);
}
TextHolder::~TextHolder(){}
void TextHolder::setText( char * st, unsigned int textSize) {
    if(textObj)
        textObj->setString( st );
    else{
        if(textfont)
            textObj = new sf::Text( st, *textfont, textSize );
        else{
            textfont = new sf::Font();
            textfont->loadFromFile(fontpath);
            textObj  = new sf::Text( st, *textfont, textSize );
        }
    }
}
void TextHolder::floatToString( float f , char * s ) const{
    char * t = (char*)malloc(4*sizeof(float));
    sprintf(t, "%0.6f", f);
    printf( "%s\n", t );
    memcpy(s, t, 4*sizeof(float));
}
void TextHolder::update(float dt) const{
    float t = dt;
    char b[4*sizeof(float)];
    floatToString( t, b );
    textObj->setString( b );
}
void TextHolder::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //states.transform *= textObj->getTransform();
    printf("Drawing text!\n");
	target.draw( *textObj , states );
}
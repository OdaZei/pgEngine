#include "include/TextHolder.hpp"
#include "include/filepaths.hpp"

#include <cstring>
TextHolder::TextHolder(): UiElement(0, 0 , 0){
}
    
TextHolder::TextHolder(  const char * st, unsigned int textSize, int x, int y ): UiElement(0, x, y ), textfield(st), textfont(nullptr) {
    textfont = new sf::Font();
    textfont->loadFromFile(fontpath);
    textObj = new sf::Text( sf::String(textfield) , *textfont, textSize);
    textObj->setStyle(sf::Text::Bold);
    textObj->setFillColor(sf::Color::White);
    textObj->setPosition((int)xPos,(int)yPos);
}
TextHolder::TextHolder( const UiElement& e): UiElement(e){
    textfont = new sf::Font();
    textfont->loadFromFile(fontpath);
    textObj = new sf::Text( sf::String(textfield) , *textfont, _DEFAULT_TEXT_SIZE_);
    textObj->setStyle(sf::Text::Bold);
    textObj->setFillColor(sf::Color::White);
    textObj->setPosition((int)xPos,(int)yPos);
}
TextHolder::~TextHolder(){}
void TextHolder::setText( char st[32], unsigned int textSize) {
    if(textObj)
        textObj->setString( sf::String(st) );
    else{
        if(textfont)
            textObj = new sf::Text( st, *textfont, _DEFAULT_TEXT_SIZE_ );
        else{
            textfont = new sf::Font();
            textfont->loadFromFile(fontpath);
            textObj  = new sf::Text( st, *textfont, _DEFAULT_TEXT_SIZE_ );
        }
    }
}
void TextHolder::floatToString( float f , char * s ) const{
    char * t = (char*)malloc(4*sizeof(float));
    sprintf(t, "%0.6f", f);
    memcpy(s, t, 4*sizeof(float));
}
void TextHolder::update(float dt) const{
    float t = dt;
    char b[4*sizeof(float)];
    floatToString( t, b );
    textObj->setString( b );
}
void TextHolder::updateC ( char arr[32] ){
    setText( arr, _DEFAULT_TEXT_SIZE_ );
}
void TextHolder::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //states.transform *= textObj->getTransform();
	target.draw( *textObj , states );
}
const sf::String TextHolder::getText() {
    return textObj->getString();
}
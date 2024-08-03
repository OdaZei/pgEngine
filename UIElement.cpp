#include "include/UIElement.hpp"

UiElement::UiElement( unsigned int t , int x, int y): index(0), type(t), xPos(x), yPos(y){
    //;
}

UiElement::~UiElement( ){ /* */ }


void UiElement::setIndex( unsigned int ind ) {
    index = ind;
}
void UiElement::update(float dt ) const {
}
void UiElement::drawCurrent (sf::RenderTarget& target, sf::RenderStates states)  const{

}
unsigned int UiElement::getType( ) {
    return type;
}
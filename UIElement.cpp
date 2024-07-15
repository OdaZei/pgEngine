#include "include/UIElement.hpp"

UiElement::UiElement( ): index(0) {
    //;
}
UiElement::~UiElement( ){ /* */ }

/*
void UiElement::draw ( sf::RenderTarget& target, sf::RenderStates states ) const {
    //
    drawCurrent( target, states );
*/
void UiElement::setIndex( unsigned int ind ) {
    index = ind;
}
void UiElement::update(float dt ) const {
}
void UiElement::drawCurrent (sf::RenderTarget& target, sf::RenderStates states)  const{

}

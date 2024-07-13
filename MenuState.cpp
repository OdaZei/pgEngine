#include <SFML/Graphics/Text.hpp>

#include "include/MenuState.hpp"
#include "include/filepaths.hpp"

MenuState::MenuState( GameState* gstate ): EngineState(1), gState_(gstate), font( nullptr ) {
    font = new sf::Font();
    font->loadFromFile( fontpath );
}

EngineState* MenuState::handleEvents( const sf::Event& e) {
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Space){
            return gState_;
        }
        if (e.key.code == sf::Keyboard::Backspace) {
            gState_->reset(); //Restart
            return gState_;
        }
    }
    return nullptr; //keep current state;
}
void MenuState::update( float dt ) {
    // Do none;
}
void MenuState::render(sf::RenderTarget* target) {
    //draw the menu
    sf::Text text("Press Space To Start !", *font);
    text.setCharacterSize(30);
    //text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition( -125 , -10);
    target->draw(text);
    
}
sf::View MenuState::getCamera(int mode) {
    return sf::View(sf::Vector2f(0,0), sf::Vector2f(680,480));
}
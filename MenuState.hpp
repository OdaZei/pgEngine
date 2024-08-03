#pragma once

#include <SFML/Graphics/Font.hpp>

#include "EngineState.hpp"
#include "GameState.hpp"

class MenuState: public EngineState {
    public:
        MenuState( GameState*);
        EngineState* handleEvents( const sf::Event&) override;
        void update(float) override;
        void render(sf::RenderTarget* target) override;
        sf::View getCamera(int) override;
    private:
        GameState*  gState_;
        sf::Font*   font;
};
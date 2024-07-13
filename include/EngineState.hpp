#pragma once

#include <SFML/Window/Event.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

class EngineState {
    public :
        EngineState(int t);
        virtual ~EngineState() = default;
        virtual EngineState* handleEvents( const sf::Event&) = 0;
        virtual void update( float dt ) = 0;
        virtual void render(sf::RenderTarget*) = 0;
        virtual sf::View getCamera(int) = 0;

        int type;
};
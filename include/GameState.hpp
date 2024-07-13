#pragma once


#include "EngineState.hpp"
#include "EntityManager.hpp"
#include "WorldManager.hpp"
#include "Camera.hpp"

class GameState: public EngineState {
    public:
        GameState();
        EngineState* handleEvents( const sf::Event&) override;
        void update(float) override;
        void render(sf::RenderTarget*) override;
        void reset( );
        sf::View getCamera(int) override;
    private:
        GameState* gState_;
        
        Entities*   entManager;
        World*      world;
        Camera*     camera;
        Camera*     miniMap;
};
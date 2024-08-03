#pragma once


#include "EngineState.hpp"
#include "WEManager.hpp"
#include "Camera.hpp"
#include "UiManager.hpp"


class GameState: public EngineState {
    public:
        GameState();
        EngineState* handleEvents( const sf::Event&) override;
        void update(float) override;
        void render(sf::RenderTarget*) override;
        void reset( );
        sf::View getCamera(int) override;
    protected:
        bool menuIsOpen;
        int  menuIndex;
    private:
        GameState* gState_;
        
        WEM*        weM;
        Camera*     camera;
        UiManager * uiman;
};
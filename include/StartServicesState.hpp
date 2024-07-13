#pragma once

#include "WindowManager.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"

class StartServicesState {
    public:
        StartServicesState();
        void handleEvents( ) ;
        void update( float dt ) ;
        void render();
        bool isWindowOpen();
    private:
        WindowManager* WinMan;
        
        MenuState* mState_;
        GameState* gState_;

        EngineState* cState_;

};
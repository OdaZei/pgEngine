#include "include/StartServicesState.hpp"

StartServicesState::StartServicesState( ): WinMan(nullptr),mState_(nullptr), gState_(nullptr), cState_(nullptr) {
    WinMan = new WindowManager();
    gState_ = new GameState();
    mState_ = new MenuState( gState_ );
    cState_ = mState_;
}
void StartServicesState::handleEvents( ) {
    sf::Event event;
    while(WinMan->windowPoll( &event )){
        if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed) )
            WinMan->windowClose();
        EngineState* nState = cState_->handleEvents(event);
        if(nState)
            cState_ = nState;
    }
}
void StartServicesState::update( float dt ) {
    if( cState_ ){
        WinMan->setView(cState_->getCamera(0));
        cState_->update( dt );
    }
}
void StartServicesState::render() {
    WinMan->Clear();
    if( cState_ && WinMan ) cState_->render(WinMan->getRenderWindow());
    WinMan->windowDisplay();
    
}
bool StartServicesState::isWindowOpen( ) {
    return WinMan->isOpened();
}
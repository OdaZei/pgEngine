#include "include/GameState.hpp"
#include "include/Menu.hpp"

char arr[32] {"Menu or so"};

GameState::GameState(): EngineState(2), gState_( nullptr ), weM(nullptr) ,camera(nullptr), uiman(nullptr), menuIsOpen(false), menuIndex(-1) {
    weM = new WEM();

    // Setting window scale, throught the camera viewport;
    sf::Vector2f cameraScale = sf::Vector2f( 80 , 80 );
    camera = new Camera(0,0,cameraScale.x,cameraScale.y, true, -cameraScale.x,-cameraScale.y, 256, 256);
    
    uiman = new UiManager(0,0, 480, 480);
    
    menuIndex = uiman->addMenu( 340 , 240 , arr);
    menuIsOpen = true;
}
std::shared_ptr<UiElement*> menu;
EngineState* GameState::handleEvents( const sf::Event& e) {
    weM->handleEvents( e );
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            gState_->reset(); //Restart
            return gState_;
        }

    }
    return nullptr;
}

void GameState::update( float dt ) {

    weM->update( dt );
    uiman->updateF(0,dt); // update fps text;};
    
    //Update corrdinate text
    char arr2[32];
    sprintf(arr2, "X:%0.1f,Y:%0.1f,Z:%0.1f",weM->getOrigin().x, weM->getOrigin().y, 1.f );
    uiman->updateTC(1, arr2);
    sprintf( arr, "Tick: %.4f", dt );
    uiman->updateC(1,arr);
    
    char arr1[32];
    sprintf(arr1, "Accel: %0.5f", weM->getPlayerAccel());
    uiman->updateC( 1,arr1);
    
    camera->moveCamera( weM->getOrigin().x  , weM->getOrigin().y  , dt);
    
}
void GameState::render( sf::RenderTarget* target) {
    target->setView( camera->getCamera() );
    weM->render( target );

    //Render ui
    target->setView( uiman->getCamera() );
    uiman->render( *target, sf::RenderStates::Default );
}
void GameState::reset( ) {
    //
}
sf::View GameState::getCamera(int type) {
    return camera->getCamera();
}

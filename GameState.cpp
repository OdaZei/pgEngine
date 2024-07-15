#include "include/GameState.hpp"
#include "include/UiManager.hpp"

UiManager * uiman;

GameState::GameState(): menuIsOpen(false), menuIndex(-1), EngineState(2), gState_( nullptr ), entManager( nullptr )\
, world( nullptr ), camera(nullptr), miniMap(nullptr) {
    entManager = new Entities();

    float OriginX = 0.f, OriginY = 0.f;
	sf::Vector2f v = sf::Vector2f( OriginX , OriginY );

	entManager->addEntity( Entities::entitiesType::empty_block, v , .0f);

    /*offset player position to check custom  transform position*/
    v = sf::Vector2f( OriginX  , OriginY + 8 );

    entManager->addEntity( Entities::entitiesType::player, v , .0f);

    /*Map and camera position on initialize*/
    camera = new Camera(0,0,340,240);
    sf::Vector2f view = camera->getViewSize();

    world = new World(-120,-120,0.02f, 0.5,2.0, 0.5);
    uiman = new UiManager(0,0, 480, 480);
}
EngineState* GameState::handleEvents( const sf::Event& e) {
    entManager->handleEvents( e );
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            gState_->reset(); //Restart
            return gState_;
        }
        if(e.key.code == sf::Keyboard::E && !menuIsOpen){
            menuIndex = uiman->addMenu( 340 , 240 );
            menuIsOpen = true;
        }else if (e.key.code == sf::Keyboard::E && menuIsOpen){
            if(menuIndex != -1){
                uiman->popElement(menuIndex);
                menuIndex = -1;
                menuIsOpen = false;
            }
        }

    }
    return nullptr;
}

void GameState::update( float dt ) {

    entManager->updateEntities( dt );
    uiman->update(0,dt);
    char arr[32] {"Explore the sourroundings"};
    if(menuIsOpen) uiman->update(1, arr);
    world->getMapImage( entManager->getPlayerCtrlPos().x, entManager->getPlayerCtrlPos().y, -120,-120 );
    camera->moveCamera( entManager->getPlayerCtrlPos().x, entManager->getPlayerCtrlPos().y, dt);
    //miniMap->moveCamera( entManager->getPlayerCtrlPos().x, entManager->getPlayerCtrlPos().y, dt);
}
void GameState::render( sf::RenderTarget* target) {
    sf::Vector2f  v = entManager->getPlayerCtrlPos();
    sf::Vector2f  dView = camera->getViewSize();
    target->setView( camera->getCamera() );
    world->drawmap(target, sf::RenderStates::Default);
    entManager->drawEntities(target, sf::RenderStates::Default);
    target->setView( uiman->getCamera() );
    uiman->render( *target, sf::RenderStates::Default );
}
void GameState::reset( ) {
    //
}
sf::View GameState::getCamera(int type) {
    return camera->getCamera();
}

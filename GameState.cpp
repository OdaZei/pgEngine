#include "include/GameState.hpp"
/*@DeBug*/
#include "include/TextHolder.hpp"

TextHolder * textHl;

GameState::GameState(): EngineState(2), gState_( nullptr ), entManager( nullptr )\
, world( nullptr ), camera(nullptr), miniMap(nullptr) {
    entManager = new Entities();

    float OriginX = 0.f, OriginY = 0.f;
	sf::Vector2f v = sf::Vector2f( OriginX , OriginY );

	entManager->addEntity( Entities::entitiesType::empty_block, v , .0f);

    /*offset player position to check custom  transform position*/
    v = sf::Vector2f( OriginX  , OriginY + 8 );

    entManager->addEntity( Entities::entitiesType::player, v , .0f);

    /*Map and camera position on initialize*/
    camera = new Camera(0,0,170,120);
    sf::Vector2f view = camera->getViewSize();

    world = new World(0,0,0.02f, 0.5,2.0, 0.5);

    /*MiniMap*/
    miniMap = new Camera(0,0,170,120);

    textHl = new TextHolder( "OxDeF0", 0, 0 );
}
EngineState* GameState::handleEvents( const sf::Event& e) {
    entManager->handleEvents( e );
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            gState_->reset(); //Restart
            return gState_;
        }
    }
    return nullptr;
}

void GameState::update( float dt ) {
    //upd
    printf( "<<Game State update>: delta: %f \n", dt );
    entManager->updateEntities( dt );
    char arr[256];
    sprintf( arr, "%f", 1000 / dt ); 

    textHl->setText( arr );
    camera->moveCamera( entManager->getPlayerCtrlPos().x, entManager->getPlayerCtrlPos().y, dt);
    //miniMap->moveCamera( entManager->getPlayerCtrlPos().x, entManager->getPlayerCtrlPos().y, dt);
}
void GameState::render( sf::RenderTarget* target) {
    sf::Vector2f  v = entManager->getPlayerCtrlPos();
    sf::Vector2f  dView = camera->getViewSize();
    target->draw( world->getMapImage(1, v.x, v.y, 0,0));
    entManager->drawEntities(target, sf::RenderStates::Default);
    textHl->drawCurrent( *target, sf::RenderStates::Default );
}
void GameState::reset( ) {
    //
}
sf::View GameState::getCamera(int type) {
    if(type == 0)
        return camera->getCamera();
    return miniMap->getCamera();
}

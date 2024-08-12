#include "include/WEManager.hpp"

sf::RenderStates states = sf::RenderStates::Default;
WEM::WEM( ) {

    sprSheet = new SpriteSheet();

    Entities  e = Entities( sprSheet );
    /* Initializes world manager;
        params:  /x pos origin /y pos origin /frequency /amplitude /lacunarity/persistence/Class SpriteSheet */
    World  wm = World(-120,-120,0.02f, 0.5,2.0, 0.5, sprSheet);
    
    sf::Vector2f v = sf::Vector2f( 0  , 0 );
    
    woMan = std::make_unique<World>( wm );
    
    e.addEntity( Entities::entitiesType::player, v , .0f);
    printf( "Beeep\n" );
    enMan = std::make_unique<Entities>( e );
    printf( "Beeep2\n" );
}
WEM::~WEM( ) {

}
void WEM::setTiles( int _x, int _y ) {
    // Get Player closest tiles 8 coordinate; ( Debug )
    //std::vector<int> t = woMan->getTile(_x / 8 ,_y / 8, *enMan->getPlayerCtrlCollider());
    //enMan->updatePlayerTiles( t );
}
void WEM::update( float dt ) {
    woMan->getMapImage( 0 , 0 ,0, 0);
    enMan->updateEntities( dt );
}
void WEM::render( sf::RenderTarget* target ) {
    woMan->drawmap( target, states);
    enMan->drawEntities( target,states);   
}
void WEM::handleEvents( const sf::Event& e ) {
    enMan->handleEvents( e );
}
sf::Vector2f WEM::getOrigin( ) {
    return enMan->getPlayerCtrlPos();
}
float WEM::getPlayerAccel( ){
    return enMan->getPlayerData( 0 );
}
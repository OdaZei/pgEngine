#include <algorithm>

#include "include/EntityManager.hpp"
#include "include/ResourcesManager.hpp"

// Empty constrytuctor
Entities::Entities(SpriteSheet * sprites ): \
entities( std::unordered_map<std::shared_ptr<Object*>,  std::shared_ptr<sf::Vector2f>>( ) )\
, playerCtrlPos(sf::Vector2f(0,0)), playerControl(nullptr), playerExists(false), entitiesIndex(){
    sprSheet = sprites; 
    entitiesIndex = std::vector<int>();
}
Entities::~Entities(){}
std::shared_ptr<Object*> Entities::addPlayerController( sf::Vector2f pos ) {
    
    std::shared_ptr<Object*> ptr = nullptr;
    unsigned int index = 34;
    unsigned int pAnimSz = 4;
    // #64 -> player texture;
    std::vector<sf::VertexArray> animation = sprSheet->setAnimationSlice(pos.x, pos.y, index, 64, pAnimSz);
    sf::Vector2f d = sf::Vector2f(Entities::CellSize , Entities::CellSize);

    PlayerController* tempObj =  new PlayerController( pos, d, animation , sprSheet->getTexture() , index , true , pAnimSz);
    /* ojo */
    playerControl = tempObj;
    //playerCtrlPos = playerControl->getPosition();
    ptr = std::make_shared<Object*>( tempObj );
    /* ojo */
    if( ptr != nullptr )
        playerExists = true;
    return ptr;
}
// Creates Entity Object depending on entity type( EntitiesType );
void Entities::addEntity( entitiesType eT, sf::Vector2f pos, float angle ) {
    std::shared_ptr<Object*> ptr = nullptr;
    std::shared_ptr<sf::Vector2f> ppt = nullptr;
    sf::Vector2f tmp = pos;
    if( eT == Entities::entitiesType::player ){
        ptr = addPlayerController( pos );
    }else if ( eT == Entities::entitiesType::empty_block ){
        Object* block = new Object( eT, pos , sf::Vector2f( Entities::CellSize, Entities::CellSize ) , false, std::vector<sf::VertexArray>(), -1 ,nullptr, false, 0);

        sf::Color c =  sf::Color( sf::Color::Red );
        block->set_FillColor( c );

        block->set_move( pos.x , pos.y );

        ptr = std::make_shared<Object*>( block );
    }
    ppt = std::make_shared<sf::Vector2f>( tmp );
    eP pair  = std::make_pair(ptr, ppt);
    entities.insert( pair );
}
Object Entities::popEntity( sf::Vector2f pos ) {
    return Object();
}
//UPDATE ENTITIES IN UNORD-MAP: CALLING BASE METHOD UPDATE
void Entities::updateEntities( float dt ) {
    int u = 0;
    for( auto& en: entities ){
        Object* ent = *en.first;
        if(ent->oData->has_collider && playerExists) {
            if( ent->oData->type != playerControl->oData->type && playerControl->collider->CheckCollision( *ent->collider )){
                printf( "Detected Colission\n" );
                playerControl->set_move( playerControl->lookingDir.x*dt, playerControl->lookingDir.y*dt );
            }
            playerCtrlPos = playerControl->get_position();
        }
        ent->update( dt );
        u++;
    }
    if( !playerExists )
        playerCtrlPos = sf::Vector2f( 0.f, 0.f);
}
//HANDLE EVENTS ENTITIES IN UNORD-MAP: CALLING BASE METHOD HANDLEEVENTS
void Entities::handleEvents( sf::Event e ){
    for( auto& en: entities ){
        Object* ent = *en.first;
        ent->handleEvents( e );
    }
}

void Entities::drawEntities( sf::RenderTarget* target, sf::RenderStates& states){
    // /states.texture = sprSheet->getTexture();
    for( auto& en: entities){
		Object* o = *en.first; 
        o->drawCurrent(*target, states);
	}
}
sf::Vector2f Entities::getPlayerCtrlPos() {
    return playerCtrlPos;
}
Collider* Entities::getPlayerCtrlCollider() {
    return playerControl->getCollider();
}
void Entities::updatePlayerTiles( std::vector<int> t ){
    playerControl->updateNearTile( t );
}
float Entities::getPlayerData( int datatype ) {
    if( datatype == 0 ) return playerControl->getPlayerAccel();
    else return 0.0;
}
bool Entities::doesPLayerExist(){
    return playerExists;
}
#include <algorithm>

#include "include/EntityManager.hpp"
#include "include/ResourcesManager.hpp"

// Empty constrytuctor
Entities::Entities(SpriteSheet * sprites ): \
entities( std::unordered_map<std::shared_ptr<Object*>,  sf::Vector2f*>( ) )\
, playerCtrlPos(sf::Vector2f()), playerControl(nullptr), playerExists(false), entitiesIndex(){
    sprSheet = sprites; 
    entitiesIndex = std::vector<int>();
}
Entities::~Entities(){}
std::shared_ptr<Object*> Entities::addPlayerController( sf::Vector2f pos ) {
    
    std::shared_ptr<Object*> ptr = nullptr;
    unsigned int index = 0;
    // #64 -> player texture;
    sf::VertexArray vtx = sprSheet->setTextureSlice(pos.y, pos.y, index, 64);

    sf::Vector2f d = sf::Vector2f(Entities::CellSize , Entities::CellSize);
    
    PlayerController* tempObj =  new PlayerController( pos, d, vtx, sprSheet->getTexture() , index);
    /* ojo */
    playerControl = tempObj;
    
    ptr = std::make_shared<Object*>( tempObj );

    playerCtrlPos = playerControl->getPosition();
    /* ojo */
    if( ptr )
        playerExists = true;
    return ptr;
}
// Creates Entity Object depending on entity type( EntitiesType );
void Entities::addEntity( entitiesType eT, sf::Vector2f pos, float angle ) {
    std::shared_ptr<Object*> ptr = nullptr; 
    sf::Vector2f p = pos;
    if( eT == Entities::entitiesType::player ){
        ptr = addPlayerController( p );
    }else if ( eT == Entities::entitiesType::empty_block ){
        /* Creates base Game Object;
        *  Type      :et;
        *  Posiition : p :->: sf::Vector2f;
        *  Dimension     :->: sf::Vector2d;
        *  HasTexture    :->: bool;
        *  If has texture is false default vertex array, textureIndex -1 ; no texture; set rectangle shape
        */
        Object* block = new Object( eT, p , sf::Vector2f( Entities::CellSize, Entities::CellSize ) , false, sf::VertexArray(), -1 ,nullptr);

        sf::Color c =  sf::Color( sf::Color::Red );
        block->set_FillColor( c );

        block->set_move( p.x , p.y );

        ptr = std::make_shared<Object*>( block );
    }
    eP pair  = std::make_pair(ptr, &p);
    entities.insert( pair );
}
Object Entities::popEntity( sf::Vector2f pos ) {
    return Object();
}
//UPDATE ENTITIES IN UNORD-MAP: CALLING BASE METHOD UPDATE
void Entities::updateEntities( float dt ) {
    for( auto& en: entities ){
        Object* ent = *en.first;
        
        if(ent->oData->hasCollider) {
            if( ent->oData->type != playerControl->oData->type && playerControl->collider->CheckCollision( *ent->collider )){    
                playerControl->set_move( playerControl->lookingDir.x*dt, playerControl->lookingDir.y*dt );
            }
        }
        ent->update( dt );
    }
    playerCtrlPos = playerControl->get_position();
}
//HANDLE EVENTS ENTITIES IN UNORD-MAP: CALLING BASE METHOD HANDLEEVENTS
void Entities::handleEvents( sf::Event e ){
    for( auto& en: entities ){
        Object* ent = *en.first;
        ent->handleEvents( e );
    }
}

void Entities::drawEntities( sf::RenderTarget* target, sf::RenderStates& states){
    //states.texture = sprSheet->getTexture();
    for( auto& en: entities){
		Object* o = *en.first;
        //printf( " Drawing \n" ); 
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

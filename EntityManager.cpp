#include "include/EntityManager.hpp"
#include <algorithm>

Entities::Entities(): \
entities( std::unordered_map<std::shared_ptr<Object*>, sf::Vector2f*>( ) )\
, playerCtrlPos(sf::Vector2f()), playerControl(nullptr), playerExists(false) { }
Entities::~Entities(){}
std::shared_ptr<Object*> Entities::addPlayerController( sf::Vector2f pos ) {
    
    std::shared_ptr<Object*> ptr = nullptr; 
    
    sf::Vector2f d = sf::Vector2f(Entities::CellSize , Entities::CellSize);
    PlayerController* tempObj =  new PlayerController(pos, d);

    sf::Color c =  sf::Color( sf::Color::White );
    tempObj->set_FillColor( c );
    
    //tempObj->setOrigin( pos.x , pos.y  );
    
    playerControl = tempObj;
    playerControl->set_position(pos.x, pos.y);
    playerControl->set_dimensions(d);

    ptr = std::make_shared<Object*>( tempObj );
    
    playerCtrlPos = playerControl->get_position();
    
    if( ptr )
        playerExists = true;

    return ptr;
}
void Entities::addEntity( entitiesType eT, sf::Vector2f pos, float angle ) {
    std::shared_ptr<Object*> ptr = nullptr; 
    sf::Vector2f p = pos;
    if( eT == Entities::entitiesType::player ){
        ptr = addPlayerController( p );
    }else if ( eT == Entities::entitiesType::empty_block ){
        Object* block = new Object( eT, p , sf::Vector2f( Entities::CellSize, Entities::CellSize ));

        sf::Color c =  sf::Color( sf::Color::Red );
        block->set_FillColor( c );
    
        block->set_move( p.x , p.y );

        ptr = std::make_shared<Object*>( block );
    }
    eP pair  = std::make_pair(ptr, &p);
    entities.insert( pair );
}
//UPDATE ENTITIES IN UNORD-MAP: CALLING BASE METHOD UPDATE
void Entities::updateEntities( float dt ) {
    for( auto& en: entities ){
        Object* ent = *en.first;
        
        if(ent->oData->hasCollider) {
            if( ent->oData->type != playerControl->oData->type && playerControl->collider->CheckCollision( *ent->collider )){    
                playerControl->set_move( playerControl->lookingDir.x*100*dt, playerControl->lookingDir.y*100*dt );
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
Object Entities::popEntity( sf::Vector2f pos ) {
    return Object();
}
void Entities::drawEntities( sf::RenderTarget* target, sf::RenderStates states){
    for( auto& en: entities){
		Object* o = *en.first;
        printf( " Drawing \n" ); 
        o->drawCurrent(*target, states);
	}
}
sf::Vector2f Entities::getPlayerCtrlPos() {
    return playerCtrlPos;
}
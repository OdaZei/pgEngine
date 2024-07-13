#pragma once

#include <memory>
#include <unordered_map>

#include "PlayerController.hpp"

//ALL ENTITIES SHARE TRANSFORM NODE GRAPHS( TEMPORALY SHAPE );

class Entities {
    public:
    static const int CellSize = 2; // BASE -CELL SIZE DEFINING ENTITY BOUNDARIES.  
    enum entitiesType { player, empty_block }; //ENTITY TYPES

    typedef std::pair<std::shared_ptr<Object*>, sf::Vector2f*>  eP; //entity pair

    Entities();
    ~Entities();
    
    std::shared_ptr<Object*> addPlayerController( sf::Vector2f pos );

    void addEntity( entitiesType eT, sf::Vector2f pos, float angle);
    
    Object popEntity( sf::Vector2f pos );
    
    void updateEntities( float dt );
    void handleEvents( sf::Event e );
    void drawEntities( sf::RenderTarget* target, sf::RenderStates states);
    std::unordered_map<std::shared_ptr<Object*>, sf::Vector2f*> entities;

    sf::Vector2f getPlayerCtrlPos();

    protected:
        sf::Vector2f        playerCtrlPos;
        PlayerController*   playerControl;
        bool                playerExists;
};
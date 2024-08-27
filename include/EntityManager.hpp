#pragma once

#include <memory>
#include <unordered_map>

#include "PlayerController.hpp"
#include "Tile.hpp"

//ALL ENTITIES SHARE TRANSFORM NODE GRAPHS( TEMPORALY SHAPE );

class Entities {
    public:
    static const int CellSize = 8; // BASE CELL SIZE DEFINING ENTITY BOUNDARIES.  
    enum entitiesType { player, empty_block }; //ENTITY TYPES

    typedef std::pair<std::shared_ptr<Object*>, std::shared_ptr<sf::Vector2f>>  eP; //entity pair

    Entities(SpriteSheet*);
    ~Entities();
    
    std::shared_ptr<Object*> addPlayerController( sf::Vector2f pos );

    void addEntity( entitiesType eT, sf::Vector2f pos, float angle);
    
    Object popEntity( sf::Vector2f pos );
    
    void updateEntities( float dt );
    void handleEvents( sf::Event e );
    void drawEntities( sf::RenderTarget* target, sf::RenderStates& states);
    
    std::unordered_map<std::shared_ptr<Object*>, std::shared_ptr<sf::Vector2f>> entities;

    sf::Vector2f getPlayerCtrlPos(); // player position;
    
    Collider* getPlayerCtrlCollider(); // get reference to player collider;
    
    float getPlayerData(int); // return Player accel;

    void updatePlayerTiles( std::vector<int> );

    bool doesPLayerExist();
    protected:
        sf::Vector2f        playerCtrlPos;
        
        SpriteSheet*        sprSheet;
        PlayerController*   playerControl;
        
        bool                playerExists;

        std::vector<int>    entitiesIndex;
};
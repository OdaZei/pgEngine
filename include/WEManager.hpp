#pragma once

#include "WorldManager.hpp"
#include "EntityManager.hpp"

class WEM {
    public:
        WEM();
        ~WEM();

        void update(float);
        void render(sf::RenderTarget*);
        void handleEvents(const sf::Event& );
        void setTiles( int x, int y );
        
        
        sf::Vector2f getOrigin();
        float getPlayerAccel();
    private:
        std::unique_ptr<World>      woMan;
        std::unique_ptr<Entities>   enMan;
        SpriteSheet*                sprSheet;
};
#pragma once

#include "Object.hpp"
#include "ResourcesManager.hpp"

static const sf::Color pColor = sf::Color( sf::Color::Red);

class PlayerController: public Object {
    public:
        PlayerController();
        PlayerController(sf::Vector2f pos , sf::Vector2f dim, std::vector<sf::VertexArray> vtx, sf::Texture* t, unsigned int ind , bool hAnim , unsigned int animSz );
        ~PlayerController();

        void            ColisionMovementUpdate( );

        virtual void    update( float dt ) ;
        //virtual void            drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
        virtual void    handleEvents( sf::Event e ) ;

        void            updateNearTile( std::vector<int> );
        float           getPlayerAccel();

        sf::Vector2f        lookingDir;
    protected:
        float               accel = 8.0f;
    private:
        sf::VertexArray     vA;
        std::vector<int>    nearTiles;
        sf::Vector2f        acceleration  { 0 , 0 };
        sf::Vector2f        velocity      { 0 , 0 };
        
        //sf::VertexArray    texture;
        //sf::Texture*       spritesheet;
};
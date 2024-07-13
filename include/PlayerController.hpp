#pragma once
#include "Object.hpp"

static const sf::Color pColor = sf::Color( sf::Color::Red);
class PlayerController: public Object {
    public:
        PlayerController();
        PlayerController(sf::Vector2f pos , sf::Vector2f dim);
        ~PlayerController();
        //FROM OBJECT::UPDATE
        virtual void update( float dt ) ;
        void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
        //FROM OBJEC::HANDLEEVENTS
        virtual void handleEvents( sf::Event e ) ;

        sf::Vector2f lookingDir;
    private:
        //CURRENT VELOCITY VALUE
        sf::Vector2f velocity {0,0};
        //PLAYER LOOKING DIRECTION
};
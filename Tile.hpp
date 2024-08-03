#pragma once
#include <memory>
#include "Collider.hpp"
class Tile {
    public:
        Tile(int, int, int, bool, bool);
        ~Tile();
        bool isColliding( int , int , Collider );
        void setTileId( int _id );
        int getId( );
        bool hasColl();

    protected:
        int id;
        int xPos;
        int yPos;
        bool isWalkable;
        bool hasCollider;
    private:
        Collider* collider;
};
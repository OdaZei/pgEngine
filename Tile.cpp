#include "include/Tile.hpp"

Tile::Tile( int i, int x, int y, bool w, bool c ): id(i), xPos(x), yPos(y), isWalkable(w), hasCollider(c), collider(nullptr){
    //iswalkable for future use maybe different block hights 3 dim;
    if(hasCollider){
        collider  = new Collider( sf::Vector2f(xPos, yPos) , sf::Vector2f(4 , 4) );
        collider->SetVertexAxis( sf::Vector2f(xPos, yPos) , sf::Vector2f(4, 4));
    }
}
Tile::~Tile(){

}

bool Tile::isColliding( int x, int y, Collider other ) {
    if(hasCollider){
        //other pos
        collider->CheckCollision(other);
        printf( "\n\nColliding\n\n" );
        return true;
    }
    return false;
}
void Tile::setTileId( int _id ){
    id = _id;
}
int Tile::getId(){
    return id;
}
bool Tile::hasColl(){
    return hasCollider;
}
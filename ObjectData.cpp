#include "include/ObjectData.hpp"

ObjectData::ObjectData( ) {
    hasCollider = false;
    canMove     = false;
}
ObjectData::ObjectData( int t , bool cc, bool cm ) {
    type        =  t;
    hasCollider = cc;
    canMove     = cm;
}
ObjectData::~ObjectData() { }
#include "include/ObjectData.hpp"

ObjectData::ObjectData( ) {
    type          = -1;
    has_collider  = false;
    can_move      = false;
    has_texture   = false;
    has_animation = false;
    num_textures  = 0;
}
ObjectData::ObjectData( int t , bool cc, bool cm, bool ht, bool ha, unsigned int nt) {
    type            =  t;
    has_collider    = cc;
    can_move        = cm;
    has_texture     = ht;
    has_animation   = ha;
    num_textures    = nt;
}
ObjectData::~ObjectData() { }
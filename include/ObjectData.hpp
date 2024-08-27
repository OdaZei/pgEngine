#pragma once

typedef struct ObjectData{
    int             type;
    bool            has_collider;
    bool            can_move;

    bool            has_texture;
    bool            has_animation;
    unsigned int    num_textures;

    ObjectData();
    ObjectData(int, bool, bool, bool, bool, unsigned int);
    ~ObjectData();


}ObjectData;
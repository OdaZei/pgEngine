#pragma once

typedef struct ObjectData{
    int type;
    bool hasCollider;
    bool canMove;

    ObjectData();
    ObjectData(int, bool, bool);
    ~ObjectData();

}ObjectData;
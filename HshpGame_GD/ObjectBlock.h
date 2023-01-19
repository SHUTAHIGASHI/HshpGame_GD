#pragma once
#include "ObjectBase.h"

class ObjectBlock :
    public ObjectBase
{
public:
    ObjectBlock();
    ~ObjectBlock(){}

    void Init();

    void SetPos();

    void Update();

    void Draw();

    bool CollisionCheck(float X, float Y);
};


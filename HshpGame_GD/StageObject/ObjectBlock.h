#pragma once
#include "ObjectBase.h"

class ObjectBlock :
    public ObjectBase
{
public:
    ObjectBlock();
    ~ObjectBlock(){}

    void Init(float X, float Y);

    void Update();

    void Draw();
};

#pragma once
#include "ObjectBase.h"

class ObjectBlock :
    public ObjectBase
{
public:
    ObjectBlock();
    ~ObjectBlock(){}

    void Init();

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);
};

#pragma once
#include "ObjectBase.h"

class ObjectGravityPad :
    public ObjectBase
{
public:
    ObjectGravityPad();
    ~ObjectGravityPad() {}

    void Init(float X, float Y);

    void Update();

    void Draw();

private:
};


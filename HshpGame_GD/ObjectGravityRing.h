#pragma once
#include "ObjectBase.h"

class ObjectGravityRing :
    public ObjectBase
{
public:
    ObjectGravityRing();
    ~ObjectGravityRing() {}

    void Init(float X, float Y);

    void Update();

    void Draw();

private:
    float circleSize;
    float sizeAcc;
};


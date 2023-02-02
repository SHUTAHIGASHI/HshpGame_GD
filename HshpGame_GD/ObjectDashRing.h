#pragma once
#include "ObjectBase.h"

class ObjectDashRing :
    public ObjectBase
{
public:
    ObjectDashRing();
    ~ObjectDashRing() {}

    void Init();

    void SetPos(float X, float Y);

    void Update();

    void Draw();

private:
    float circleSize;
    float sizeAcc;
};


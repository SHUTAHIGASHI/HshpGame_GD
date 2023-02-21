#pragma once
#include "ObjectBase.h"

class ObjectRingBase :
    public ObjectBase
{
public:
    ObjectRingBase();
    ~ObjectRingBase() {}

    virtual void Init();

    virtual void SetPos(float X, float Y);

    virtual void Update();

    virtual void Draw(int color);

private:
    float circleSize;
    float sizeAcc;
};


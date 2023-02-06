#pragma once
#include "ObjectBase.h"

class ObjectReverseRing :
    public ObjectBase
{
public:
    ObjectReverseRing();
    ~ObjectReverseRing() {}

    void Init();

    void SetPos(float X, float Y);

    void Update();

    void Draw();

private:
    float circleSize;
    float sizeAcc;
};


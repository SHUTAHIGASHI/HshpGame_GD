#pragma once
#include "ObjectBase.h"

class ObjectJumpRing :
    public ObjectBase
{
public:
    ObjectJumpRing();
    ~ObjectJumpRing() {}

    void Init(float X, float Y);

    void Update();

    void Draw();

private:
    float circleSize;
    float sizeAcc;
};


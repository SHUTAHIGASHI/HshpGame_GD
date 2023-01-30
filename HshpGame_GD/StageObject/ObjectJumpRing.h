#pragma once
#include "ObjectBase.h"

class ObjectJumpRing :
    public ObjectBase
{
public:
    ObjectJumpRing();
    ~ObjectJumpRing() {}

    void Init();

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);

private:
    float circleSize;
    float sizeAcc;
};


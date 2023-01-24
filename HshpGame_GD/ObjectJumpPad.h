#pragma once
#include "ObjectBase.h"

class ObjectJumpPad :
    public ObjectBase
{
public:
    ObjectJumpPad();
    ~ObjectJumpPad() {}

    void Init(float X, float Y);

    void Update();

    void Draw();

private:
};


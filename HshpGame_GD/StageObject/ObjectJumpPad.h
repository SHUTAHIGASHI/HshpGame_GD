#pragma once
#include "ObjectBase.h"

class ObjectJumpPad :
    public ObjectBase
{
public:
    ObjectJumpPad();
    ~ObjectJumpPad() {}

    void Init();

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);

private:
};


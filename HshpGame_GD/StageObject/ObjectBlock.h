#pragma once
#include "ObjectBase.h"

class ObjectBlock :
    public ObjectBase
{
public:
    ObjectBlock();
    ~ObjectBlock(){}

    void Init(int hBlock);

    void SetPos(float X, float Y);

    void Update();

    void Draw();

private:
    int m_hBlock;
};

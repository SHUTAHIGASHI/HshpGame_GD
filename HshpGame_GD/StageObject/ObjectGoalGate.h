#pragma once
#include "ObjectBase.h"

class ObjectGoalGate :
    public ObjectBase
{
public:
    ObjectGoalGate();
    ~ObjectGoalGate() {}

    void Init(int hPortal);

    void SetPos(float X, float Y);

    void Update();

    void Draw();
private:
    int m_countFrame;
    int m_drawFrame = 0;
    
    int m_hPortal;

    int m_imgX;
    int m_imgY;
};

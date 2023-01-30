#pragma once
#include "ObjectBase.h"

class ObjectGoalGate :
    public ObjectBase
{
public:
    ObjectGoalGate();
    ~ObjectGoalGate() {}

    void Init();

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);
};

#pragma once
#include "SceneBase.h"
#include "game.h"

class SceneDemo :
    public SceneBase
{
public:
    SceneDemo();
    ~SceneDemo();

    void Init();

    void Update(const InputState& input, NextSceneState& nextScene);

    void Draw();
private:
    using m_tUpdateFunc = void (SceneDemo::*) (const InputState& input, NextSceneState& nextScene);
    m_tUpdateFunc m_updateFunc = nullptr;

    void NormalUpdate(const InputState& input, NextSceneState& nextScene);

    void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

    void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);
private:
    int m_countFrame;
    int m_fadeCount;
};


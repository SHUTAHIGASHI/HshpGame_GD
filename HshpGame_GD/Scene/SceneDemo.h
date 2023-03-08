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

    void End();

    void Update(const InputState& input, NextSceneState& nextScene);

    void Draw();
private:
    using m_tUpdateFunc = void (SceneDemo::*) (const InputState& input, NextSceneState& nextScene);
    m_tUpdateFunc m_updateFunc = nullptr;

    void NormalUpdate(const InputState& input, NextSceneState& nextScene);

    void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

    void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);
private:
    // �t���[�����J�E���g
    int m_countFrame;
    // �t�F�[�h�p�J�E���g
    int m_fadeCount;

    // �e�L�X�g�_��
    int m_textTimer;

    // �f�����[�r�[�n���h��
    int m_hDemo;
};


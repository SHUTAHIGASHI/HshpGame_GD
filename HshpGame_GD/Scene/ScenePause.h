#pragma once
#include "SceneBase.h"
#include "game.h"
#include <string>

class SceneMain;

class ScenePause : public SceneBase
{
public:
	ScenePause() :
		m_hPadImg(-1),
		m_hSelectSound(-1),
		m_selectPos(0),
		m_selectNamePos(0),
		m_textTimer(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_pMain(nullptr)
	{
	}
	virtual ~ScenePause() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// ������
	void Init();

	// �I������
	void End();
	// �X�V
	virtual void Update(const InputState& input, NextSceneState& nextScene, bool &isPEnd);
	// �`��
	virtual void Draw();

	void DrawPadText();

private:
	// Update
	using m_tUpdateFunc = void (ScenePause::*) (const InputState& input, NextSceneState& nextScene, bool& isEnd);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene, bool& isEnd);

	// Draw
	using m_tDrawFunc = void (ScenePause::*) ();
	m_tDrawFunc m_drawFunc = nullptr;

	void NormalDraw();
private:
	// �摜�f�[�^
	int m_hPadImg;
	// ���f�[�^
	int m_hSelectSound;

	// ���j���[�I��
	int m_selectPos;
	int m_selectNamePos;

	// �e�L�X�g�_��
	int m_textTimer;

	// �����̃T�C�Y
	int m_textScale;
	int m_textScaleAcc;

	// ���̃X�e�[�W
	bool m_isNextStage;

	SceneMain* m_pMain;
};
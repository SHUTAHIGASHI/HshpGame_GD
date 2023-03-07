#pragma once
#include "SceneBase.h"
#include "game.h"
#include <string>
#include <memory>
#include <array>

class SceneRanking;
class ParticleBase;

class SceneClear : public SceneBase
{
public:
	SceneClear():
		m_hFont(-1),
		m_hOr(-1),
		m_selectPos(0),
		m_selectNamePos(0),
		m_sceneChangeDelay(0),
		m_shadowScale(0),
		m_textFadeNum(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_isEnd(false),
		m_pRanking(nullptr)
	{
	}
	virtual ~SceneClear() {}

	// ������
	virtual void Init(int font);
	
	// �I������
	void End();
	// �X�V
	virtual void Update(const InputState& input, NextSceneState& nextScene, const bool isPrac);
	// �`��
	virtual void Draw();

	bool IsNextStage() const { return m_isNextStage; }

	// m_isEnd ���擾
	virtual bool IsEnd() { return m_isEnd; }

private:
	// Update
	using m_tUpdateFunc = void (SceneClear::*) (const InputState& input, NextSceneState& nextScene, const bool isPrac);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene, const bool isPrac);

	// Draw
	using m_tDrawFunc = void (SceneClear::*) ();
	m_tDrawFunc m_drawFunc = nullptr;

	void NormalDraw();
private:
	int m_hFont;
	int m_hOr;

	// ���j���[�I��
	int m_selectPos;
	int m_selectNamePos;
	
	// �^�C�g���\���܂ł̒x���p�ϐ�
	int m_sceneChangeDelay;
	
	int m_shadowScale;
	int m_textFadeNum;

	int m_textScale;
	int m_textScaleAcc;

	// ���̃X�e�[�W
	bool m_isNextStage;
	// �V�[���I��
	bool m_isEnd;

	SceneRanking* m_pRanking;
};
#pragma once
#include "SceneBase.h"
#include "game.h"

class SceneClear : public SceneBase
{
public:
	SceneClear():
		m_selectPos(0),
		m_sceneChangeDelay(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_isEnd(false)
	{
	}
	virtual ~SceneClear() {}

	// ������
	virtual void Init();
	
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
	// ���j���[�I��
	int m_selectPos;
	
	// �^�C�g���\���܂ł̒x���p�ϐ�
	int m_sceneChangeDelay;
	
	int m_textScale;
	int m_textScaleAcc;

	// ���̃X�e�[�W
	bool m_isNextStage;
	// �V�[���I��
	bool m_isEnd;
};
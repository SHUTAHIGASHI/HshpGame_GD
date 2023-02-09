#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect() :
		m_selectPos(0),
		m_isEnd(false),
		m_hBg(-1),
		m_scroll(0),
		m_scrollAcc(0),
		m_pMain(nullptr)
	{
	}
	virtual ~SceneStageSelect() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// ������
	virtual void Init();

	// �I������
	void End();

	// �X�V����
	void Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
	// �`��
	void Draw();

	// m_isEnd ���擾
	bool IsEnd() const { return m_isEnd; }
private:
	// ���j���[�I��
	int m_selectPos;

	// �^�C�g���\�����I���邩�ǂ���
	bool m_isEnd;

	// �摜�f�[�^
	int m_hBg;

	int m_scroll;
	int m_scrollAcc;

	SceneMain* m_pMain;
};
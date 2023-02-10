#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;

class SceneTitle : public SceneBase
{
public:
	SceneTitle():
		m_updateFunc(&SceneTitle::SceneStartUpdate),
		m_selectPos(0),
		m_fadeCount(0),
		m_isEnd(false),
		m_hBg(-1),
		m_textScroll(0),
		m_scroll(0),
		m_scrollAcc(0)
	{
	}
	virtual ~SceneTitle() {}

	// ������
	virtual void Init();
	
	// �I������
	void End();

	// �X�V����
	void Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene, bool &isPrac);
	// �`��
	void Draw();

	// m_isEnd ���擾
	bool IsEnd() const { return m_isEnd; }
private:
	using m_tUpdateFunc = void (SceneTitle::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);

	void SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);

	void SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
private:	
	// ���j���[�I��
	int m_selectPos;

	int m_fadeCount;
	// �^�C�g���\�����I���邩�ǂ���
	bool m_isEnd;

	// �摜�f�[�^
	int m_hBg;

	int m_textScroll;

	int m_scroll;
	int m_scrollAcc;
};
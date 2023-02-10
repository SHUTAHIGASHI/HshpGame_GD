#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;
class SceneManager;

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect() :
		m_updateFunc(&SceneStageSelect::SceneStartUpdate),
		m_selectPos(0),
		m_fadeCount(0),
		m_isEnd(false),
		m_hBg(-1),
		m_textScroll(0),
		m_scroll(0),
		m_scrollAcc(0),
		m_pMain(nullptr),
		m_pManager(nullptr)
	{
	}
	virtual ~SceneStageSelect() {}

	void SetMain(SceneMain* main) { m_pMain = main; }
	void SetManager(SceneManager* manager) { m_pManager = manager; }

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
	using m_tUpdateFunc = void (SceneStageSelect::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
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

	SceneMain* m_pMain;
	SceneManager* m_pManager;
};
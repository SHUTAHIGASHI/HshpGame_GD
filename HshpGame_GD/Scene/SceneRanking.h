#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "Stage.h"
#include "game.h"

class SceneMain;

class SceneRanking : public SceneBase
{
public:
	SceneRanking() :
		m_updateFunc(&SceneRanking::SceneStartUpdate),
		m_ranking(),
		m_savedAttempt(),
		m_stageState(StageState::firstStage),
		m_selectPos(0),
		m_textTimer(0),
		m_fadeCount(0),
		m_isEnd(false),
		m_hBg(-1),
		m_pMain(nullptr)
	{
	}
	virtual ~SceneRanking() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// ������
	virtual void Init();

	// �I������
	void End();

	// �X�V����
	void Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
	// �`��
	void Draw();

	void SetRanking(int attempt, StageState stage);

	void SaveRankingData();

	void LoadRankingData();

	// m_isEnd ���擾
	bool IsEnd() const { return m_isEnd; }
private:
	using m_tUpdateFunc = void (SceneRanking::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	void SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
private:
	// �����L���O�p�z��
	int m_ranking[10];
	int m_savedAttempt[10];
	
	StageState m_stageState;

	// ���j���[�I��
	int m_selectPos;

	int m_textTimer;

	int m_fadeCount;
	// �^�C�g���\�����I���邩�ǂ���
	bool m_isEnd;

	// �摜�f�[�^
	int m_hBg;

	SceneMain* m_pMain;
};
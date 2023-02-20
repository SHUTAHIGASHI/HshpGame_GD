#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "Stage.h"
#include "game.h"
#include <string>

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
		m_isRankIn(false),
		m_isEnd(false),
		m_hBg(-1),
		m_hFont(-1),
		m_pMain(nullptr)
	{
	}
	virtual ~SceneRanking() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// ������
	virtual void Init(int font);

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

	bool IsRankIn() const { return m_isRankIn; }
	void ResetRankIn() { m_isRankIn = false; }
	void SetPlayerName(std::string name) { m_playerName[1] = name; }

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
	
	std::string m_playerName[10];
	
	StageState m_stageState;

	// ���j���[�I��
	int m_selectPos;

	int m_textTimer;

	int m_fadeCount;
	
	bool m_isRankIn;
	// �^�C�g���\�����I���邩�ǂ���
	bool m_isEnd;

	// �摜�f�[�^
	int m_hBg;
	// �����f�[�^
	int m_hFont;

	SceneMain* m_pMain;
};
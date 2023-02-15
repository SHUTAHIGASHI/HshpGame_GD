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

	// 初期化
	virtual void Init();

	// 終了処理
	void End();

	// 更新処理
	void Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
	// 描画
	void Draw();

	void SetRanking(int attempt, StageState stage);

	void SaveRankingData();

	void LoadRankingData();

	// m_isEnd を取得
	bool IsEnd() const { return m_isEnd; }
private:
	using m_tUpdateFunc = void (SceneRanking::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	void SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
private:
	// ランキング用配列
	int m_ranking[10];
	int m_savedAttempt[10];
	
	StageState m_stageState;

	// メニュー選択
	int m_selectPos;

	int m_textTimer;

	int m_fadeCount;
	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hBg;

	SceneMain* m_pMain;
};
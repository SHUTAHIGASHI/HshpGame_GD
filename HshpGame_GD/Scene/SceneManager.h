#pragma once

#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneStageSelect.h"
#include "SceneRanking.h"
#include "SceneHowTo.h"

class SceneManager
{
public:
	// シーンの種類定義
	typedef enum SceneKind
	{
		kSceneTitle,
		kSceneHowTo,
		kSceneRanking,
		kSceneStageSelect,
		kSceneMain,
		kSceneClear,

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	// 初期化
	void Init(int font);
	// 削除
	void End();

	// 更新
	void Update(const InputState& input, int font, bool &isGameEnd);
	// 描画
	void Draw();

	SceneKind GetLastScene() { return m_lastScene; }
	NextSceneState GetNextScene() { return m_nextScene; }

private:
	// 練習モード
	bool m_isPrac;
	
	SceneKind m_kind;
	SceneKind m_lastScene;
	NextSceneState m_nextScene;

	SceneTitle	m_title;
	SceneStageSelect m_stageSelect;
	SceneHowTo m_howTo;
	SceneRanking m_ranking;
	SceneMain	m_main;
	SceneClear	m_clear;
};
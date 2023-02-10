#pragma once

#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneStageSelect.h"

class SceneManager
{
public:
	// シーンの種類定義
	typedef enum SceneKind
	{
		kSceneTitle,
		kSceneHelp,
		kSceneStageSelect,
		kSceneMain,
		kSceneClear,

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	// 初期化
	void Init(SceneKind kind = kSceneTitle);
	// 削除
	void End();

	// 更新
	void Update(const InputState& input, bool &isGameEnd);
	// 描画
	void Draw();

	SceneKind GetLastScene() { return m_lastScene; }

private:
	// 練習モード
	bool m_isPrac;
	
	SceneKind	m_kind;
	NextSceneState m_nextScene;
	SceneKind m_lastScene;

	SceneTitle	m_title;
	SceneStageSelect m_stageSelect;
	SceneMain	m_main;
	SceneClear	m_clear;
};
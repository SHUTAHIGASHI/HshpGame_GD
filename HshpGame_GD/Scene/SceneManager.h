#pragma once

#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"

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
	void update(const InputState& input, bool &isGameEnd);
	// 描画
	void Draw();

	// m_isMusicEnd を取得
	bool IsGameMusicEnd() { return m_isMusicEnd; }

private:
	// ゲーム終了
	bool m_isMusicEnd;

	// 練習モード
	bool m_isPrac;
	
	SceneKind	m_kind;
	NextSceneState m_nextScene;

	SceneTitle	m_title;
	SceneMain	m_main;
	SceneClear	m_clear;
};
#pragma once

#include "Player.h"
#include "Stage.h"
#include "ObjectBlock.h"
#include "game.h"

class SceneManager;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void SetManager(SceneManager* manager) { m_pManager = manager; }

	// 初期化
	void Init();

	void GameSetting();

	void PlayGameSound();

	// 終了処理
	void End();

	// 毎フレームの処理
	void Update(const InputState& input, NextSceneState& nextScene);
	// 毎フレームの描画
	void Draw();

	// ステージクリア時
	void OnStageClear(NextSceneState& nextScene);

	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

	// チャレンジモードにセット
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }
	// 選んだステージをセット
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

private:
	// キャラクターのグラフィックハンドル
	int m_hPlayer;
	int m_hPlayerWaveBurner;
	int m_hDeathEffect;
	// オブジェクトのグラフィックハンドル
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	// 背景のグラフィック
	int m_hBg;

	// 効果音
	int m_hDeathSound;
	// 音楽用
	int m_hPracBgm;
	int m_hChallengeBgm;
	int m_hPlayBgm;

	int m_fadeCount;

	// スクロール用
	int m_scroll;
	// ゲームの制限時間
	int m_startDelay;
	// スタート遅延時のテキストサイズ
	int m_startTextSize;
	// ゲームオーバー時の遅延時間
	int m_gameOverDelay;
	// 挑戦回数
	int m_countAttempt;

	// ゲームモード
	bool m_isPracticeMode;

	// シーン終了
	bool m_isEnd;

	// 選ばれたステージ
	StageState m_selectedStage;

	// プレイヤー
	Player m_Player;
	// ステージ
	Stage m_Stage;

	SceneManager* m_pManager;
};
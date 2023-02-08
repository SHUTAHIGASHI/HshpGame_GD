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

	// m_isGameClearを取得
	virtual bool IsGameClear() const { return m_isGameClear; }
	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

	// チャレンジモードにセット
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }

private:
	// 片側の敵の最大出現数
	static constexpr int kEnemyMax = 10;

private:
	// キャラクターのグラフィックハンドル
	int m_playerHandle;
	int m_deathEffectHandle;
	// オブジェクトのグラフィックハンドル
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	// 背景のグラフィック
	int m_hBg;

	// 音楽用
	int m_hPracBgm;
	int m_hChallengeBgm;
	int m_hPlayBgm;

	// スクロール用
	int m_scroll;
	// ゲームの制限時間
	int m_startDelay;
	// ゲームオーバー時の遅延時間
	int m_gameOverDelay;
	// 挑戦回数
	int m_countAttempt;

	// ゲームモード
	bool m_isPracticeMode;

	// ゲームクリア
	bool m_isGameClear;
	// シーン終了
	bool m_isEnd;

	// プレイヤー
	Player m_Player;
	// ステージ
	Stage m_Stage;

	SceneManager* m_pManager;
};
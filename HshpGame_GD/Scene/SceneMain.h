#pragma once
#include "game.h"
#include "Stage.h"
#include <memory>

class Player;
class Stage;
class ScenePause;
class SceneManager;
class SceneClear;
class SceneRanking;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void SetManager(SceneManager* manager) { m_pManager = manager; }
	void SetClear(SceneClear* clear) { m_pClear = clear; }
	void SetRanking(SceneRanking* rank) { m_pRanking = rank; }

	// 初期化
	void Init();

	void OnGameStart();

	void PlayGameSound();

	// 終了処理
	void End();

	// 毎フレームの処理
	void Update(const InputState& input, NextSceneState& nextScene);
	
	// リトライ選択時
	void OnRetry();

	// 毎フレームの描画
	void Draw();
	// ゲーム中の情報描画
	void DrawGameInfo();
	// ゲームスタート時のカウントダウン描画
	void DrawStartCount();

	// ステージクリア時
	void OnStageClear(NextSceneState& nextScene);

	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

	// チャレンジモードにセット
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }
	// 選んだステージをセット
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

	// 挑戦回数を取得
	int GetAttempt() const { return m_countAttempt; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// 通常の更新処理
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	// スタートカウント時の更新処理
	void StartDelayUpdate(const InputState& input, NextSceneState& nextScene);

	// シーンスタート時の更新処理
	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

private:
	// キャラクターのグラフィックハンドル
	int m_hPlayer;
	int m_hDeathEffect;
	// オブジェクトのグラフィックハンドル
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	int m_hJumpPad;
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
	// 挑戦回数描画時間
	int m_attemptDrawTime;
	// 挑戦回数描画の値
	int m_attemptDrawNum;

	// ゲームモード
	bool m_isPracticeMode;

	// ポーズ中かどうか
	bool m_isPause;
	// シーン終了
	bool m_isEnd;

	// 選ばれたステージ
	StageState m_selectedStage;

	// プレイヤー
	std::shared_ptr<Player> m_pPlayer;
	// ステージ
	std::shared_ptr<Stage> m_pStage;

	// ポーズメニューシーン
	std::shared_ptr<ScenePause> m_pPause;

	SceneManager* m_pManager;
	SceneClear* m_pClear;
	SceneRanking* m_pRanking;
};
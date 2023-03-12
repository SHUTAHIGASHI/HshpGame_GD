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

	void PlayGameLoopBgm();

	// 終了処理
	void End();

	// 毎フレームの処理
	void Update(const InputState& input, NextSceneState& nextScene);
	
	// リトライ選択時の処理
	void OnRetry();
	// 死亡時の処理
	void OnDead();

	// 毎フレームの描画
	void Draw();
	// ゲーム中の情報描画
	void DrawGameInfo();
	// ゲームスタート時のカウントダウン描画
	void OnStartCount();

	// ステージクリア時
	void OnStageClear(NextSceneState& nextScene);

	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

	// モード切り替え
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }
	virtual void SetArcadeMode() { m_isArcadeMode = true; }

	// 選んだステージをセット
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

	// 現在のステージ情報取得
	StageState GetStageState() const { return m_pStage->GetStageState(); }

	// 挑戦回数を取得
	int GetAttempt() const { return m_countAttempt; }

	// BGMハンドル取得
	int GetMusicHandle() const { return m_hPlayBgm; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// 通常の更新処理
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	// スタートカウント時の更新処理
	void StartDelayUpdate(const InputState& input, NextSceneState& nextScene);

	// シーンスタート時の更新処理
	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

	void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);

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
	int m_hPlayBgm;

	// フェード処理用カウント
	int m_fadeCount;

	// ゲームの制限時間
	int m_startDelay;
	// スタート遅延時のテキストサイズ
	int m_startTextSize;
	// スタート遅延の文字点滅
	int m_textTimer;
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
	bool m_isArcadeMode;

	// ポーズ中かどうか
	bool m_isPause;
	bool m_isPauseEnd;
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
#pragma once

#include "playerCube.h"
#include "Stage.h"
#include "ObjectBlock.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	void Init();
	// 終了処理
	void End();

	// 毎フレームの処理
	void Update(const InputState& input);
	// 毎フレームの描画
	void Draw();

	// m_isGameClearを取得
	virtual bool IsGameClear() const { return m_isGameClear; }
	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

private:
	// 片側の敵の最大出現数
	static constexpr int kEnemyMax = 10;

private:
	// キャラクターのグラフィックハンドル
	int m_playerImg;
	int m_deathEffectImg;
	// オブジェクトのグラフィックハンドル
	int m_hObjectSpike;

	// ゲームの制限時間
	int m_gameTimeRemaining;
	// ゲームオーバー時の遅延時間
	int m_gameOverDelay;

	// 挑戦回数
	int m_countAttempt;

	// ゲームクリア
	bool m_isGameClear;

	// シーン終了
	bool m_isEnd;

	// プレイヤー
	PlayerCube m_Player;

	// ステージ
	Stage m_Stage;
};
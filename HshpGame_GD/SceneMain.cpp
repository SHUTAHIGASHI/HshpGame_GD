#include "DxLib.h"
#include "SceneMain.h"
#include "game.h"

namespace
{
	// 敵出現用の遅延時間
	constexpr int kSpawnDelay = 100;
	// ゲームの制限時間
	constexpr int kGameMaxTime = 1800;	
	// 死亡時の遅延
	constexpr int kGameOverDelay = 90;

	// 制限時間表示位置
	constexpr int kTimerPositionX = Game::kScreenWidthHalf - 30;
	constexpr int kTimerPositionY = Game::kStageLowerLimit + 25;

	// RGB初期値用
	constexpr int kSetColor = 255;
}

SceneMain::SceneMain()
{
	m_hBackgroundGraphic = -1;
	m_hPlayerGraphic = -1;
	m_hEnemyGraphic = -1;

	m_spawnDelay = 0;

	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

	m_isGameClear = false;
	m_isEnd = false; 
}
SceneMain::~SceneMain()
{
}

// 初期化
void SceneMain::init()
{
	// 画像データの読み込み
	m_hPlayerGraphic = LoadGraph("imagedata/playerCube.png");
	m_hEnemyGraphic = LoadGraph("imagedata/enemy.png");

	// プレイヤー画像と音の設定
	m_player.setHandle(m_hPlayerGraphic);

	// プレイヤーの初期位置設定
	m_player.setPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
	// プレイヤー初期化 
	m_player.init();

	// 各時間用変数の初期化
	m_spawnDelay = kSpawnDelay;
	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

	// シーン終了、ゲームクリアを false に初期化
	m_isGameClear = false;
	m_isEnd = false;
}

// 終了処理
void SceneMain::end()
{
	// 画像データの削除
	DeleteGraph(m_hBackgroundGraphic);
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hEnemyGraphic);
}

// 毎フレームの処理
void SceneMain::update()
{
	// 背景の表示
	DrawGraph(0, 0, m_hBackgroundGraphic, true);
	
	if (!m_gameTimeRemaining)	// ゲーム残り時間が0になった場合
	{
		m_isGameClear = true;	// ゲームクリアとシーン終了を true にする
		m_isEnd = true;			// クリア用のシーンへ移行する
	}
	else if (!m_GameOverDelay)	// ゲームオーバー遅延が0になった場合
	{
		m_isEnd = true;			// シーン終了のみを true にする			
	}							// タイトルへ戻る

	// プレイヤーの死亡判定が true の場合
	if (m_player.isDead())
	{
		// ゲームオーバー遅延を1フレームごとに減少させる
		m_GameOverDelay--;
		return;
	}

	// 1フレームごとに残り時間と敵の出現遅延を減少させる
	m_gameTimeRemaining--;
	m_spawnDelay--;

	// 出現遅延が0になった場合、敵を出現させる
	if (!m_spawnDelay)
	{
		// 出現遅延に再び定数を代入
		m_spawnDelay = kSpawnDelay;
	}

	// プレイヤーの更新処理
	m_player.update();

	// 当たり判定チェック処理
	checkCollision();
}

// 毎フレームの描画
void SceneMain::draw()
{
	// プレイヤーの描画
	m_player.draw();

	// ステージの線の表示
	DrawLine(0, Game::kStageUpperLimit, Game::kScreenWidth, Game::kStageUpperLimit, GetColor(255, 255, 255));
	DrawLine(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit, GetColor(255, 255, 255));

	// フォントサイズ設定
	SetFontSize(Game::kFontSize);
	
	// ゲームの制限時間表示 (通常は白文字、合計時間の半分を過ぎると黄色文字、5秒を過ぎると赤文字で表示される)
	int red = kSetColor;
	int green = kSetColor;
	int blue = kSetColor;
	if (m_gameTimeRemaining <= 300)
	{
		green = 0;
		blue = 0;
	}
	else if (m_gameTimeRemaining <= kGameMaxTime / 2)
	{
		green = 216;
		blue = 0;
	}
	DrawFormatString(kTimerPositionX, kTimerPositionY, GetColor(red, green, blue), "%d", m_gameTimeRemaining / 60);
}

// 当たり判定チェック処理
void SceneMain::checkCollision()
{
	/*
	// 当たっていない場合処理をスキップ
	if (EnemyLeft.getRight() <= m_player.getLeft()) continue;
	if (m_player.getRight() <= EnemyLeft.getLeft()) continue;
	if (EnemyLeft.getBottom() <= m_player.getTop()) continue;
	if (m_player.getBottom() <= EnemyLeft.getTop()) continue;
	// 当たっている場合プレイヤーを死亡判定にする
	m_player.setDead();
	*/
}
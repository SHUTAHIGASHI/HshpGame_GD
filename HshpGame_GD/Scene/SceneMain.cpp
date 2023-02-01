#include "game.h"
#include "SceneMain.h"

#include <cassert>

namespace
{
	// 敵出現用の遅延時間
	constexpr int kSpawnDelay = 100;
	// ゲームの制限時間
	constexpr int kGameMaxTime = 1800;	
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;

	// RGB初期値用
	constexpr int kSetColor = 255;

}

SceneMain::SceneMain() :
	m_playerImg(-1),
	m_deathEffectImg(-1),
	m_hObjectSpike(-1),
	m_gameTimeRemaining(0),
	m_gameOverDelay(0),
	m_countAttempt(0),
	m_isGameClear(false),
	m_isEnd(false)
{
}

SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::Init()
{
	// アドレスの設定
	m_Player.SetStage(&m_Stage);
	m_Stage.SetPlayer(&m_Player);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);

	// 画像読み込み
	m_playerImg = LoadGraph(Game::kPlayerImg);
	m_deathEffectImg = LoadGraph(Game::kPlayerDeathEffectImg);

	GameSetting();
}

void SceneMain::GameSetting()
{
	// シーン終了、ゲームクリアを false に初期化
	m_isGameClear = false;
	m_isEnd = false;
	
	// 各時間用変数の初期化
	m_gameTimeRemaining = kGameMaxTime;
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_Player.Init(m_playerImg, m_deathEffectImg);

	// ステージ初期化
	m_Stage.Init(m_hObjectSpike);
}

// 終了処理
void SceneMain::End()
{
	// 画像データの削除
	DeleteGraph(m_playerImg);
	DeleteGraph(m_deathEffectImg);
	DeleteGraph(m_hObjectSpike);
}

// 毎フレームの処理
void SceneMain::Update(const InputState& input)
{		
	if (input.IsTriggered(InputType::enter))
	{
		m_countAttempt = 0;
		m_isEnd = true;
	}
	
	// Rキーを押すとゲームリトライ
	if (input.IsTriggered(InputType::retry))
	{
		Init();
		m_countAttempt++;
	}

	m_Stage.Update();

	m_Player.Update(input);

	OnStageClear();

	// プレイヤーの死亡判定が true の場合
	if (m_Player.IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			Init();
			m_countAttempt++;
			return;
		}
		// ゲームオーバー遅延を1フレームごとに減少させる
		m_gameOverDelay--;
		return;
	}
}

// 毎フレームの描画
void SceneMain::Draw()
{
	m_Stage.Draw();

	// プレイヤーの描画
	m_Player.Draw();
	
	DrawFormatString(10, 10, 0xffffff, "Attempt : %d", m_countAttempt);
}

void SceneMain::OnStageClear()
{
	if (m_Player.IsStageClear())
	{
		if (m_Stage.GetStageState() == StageState::tenthStage)
		{
			m_countAttempt = 0;
			m_isGameClear = true;
			m_isEnd = true;
		}
		else
		{
			m_Stage.ChangeStageState();
			GameSetting();
		}
	}
}

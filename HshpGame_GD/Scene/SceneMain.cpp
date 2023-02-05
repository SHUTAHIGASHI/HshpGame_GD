#include "SceneMain.h"
#include "game.h"
#include <cassert>

namespace
{
	// スタート時の遅延時間
	constexpr int kStartDelay = 100;
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;
}

SceneMain::SceneMain() :
	m_playerHandle(-1),
	m_deathEffectHandle(-1),
	m_hObjectSpike(-1),
	m_hBg(-1),
	m_hBgm(-1),
	m_scroll(0),
	m_startDelay(0),
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
	// シーン終了変数を初期化
	m_isEnd = false;

	// アドレスの設定
	m_Player.SetStage(&m_Stage);
	m_Stage.SetPlayer(&m_Player);

	// 画像読み込み
	m_playerHandle = LoadGraph(Game::kPlayerImg);
	m_deathEffectHandle = LoadGraph(Game::kPlayerDeathEffectImg);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);
	m_hBg = LoadGraph("imagedata/bg.png");

	m_hBgm = LoadSoundMem("soundData/BACK ON TRACK_full.mp3");
	//PlaySoundMem(m_hBgm, DX_PLAYTYPE_BACK);

	// スタート遅延の初期化
	m_startDelay = kStartDelay;

	GameSetting();
}

void SceneMain::GameSetting()
{
	// ゲームクリアを初期化
	m_isGameClear = false;
	
	// 各時間用変数の初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_Player.Init(m_playerHandle, m_deathEffectHandle);

	// ステージ初期化
	m_Stage.Init(m_hObjectSpike, m_hBg);
}

// 終了処理
void SceneMain::End()
{
	// 画像データの削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_deathEffectHandle);
	DeleteGraph(m_hObjectSpike);
	DeleteGraph(m_hBg);

	DeleteSoundMem(m_hBgm);
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
		GameSetting();
		m_countAttempt++;
	}

	m_startDelay--;
	if (m_startDelay > 0) return;
	else m_startDelay = 0;

	/*m_scroll++;
	if (m_scroll > Game::kScreenWidth) m_scroll = 0;*/

	m_Stage.Update();

	m_Player.Update(input);

	OnStageClear();

	// プレイヤーの死亡判定が true の場合
	if (m_Player.IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			GameSetting();
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
	/*int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/

	m_Stage.Draw();

	// プレイヤーの描画
	m_Player.Draw();
	
	DrawFormatString(10, 10, 0xffffff, "Attempt : %d", m_countAttempt);
}

void SceneMain::OnStageClear()
{
	if (m_Player.IsStageClear())
	{
		m_countAttempt = 0;

		if (m_Stage.GetStageState() == StageState::tenthStage)
		{
			m_Stage.ChangeStageState();
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

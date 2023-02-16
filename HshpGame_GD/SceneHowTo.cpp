#include "SceneHowTo.h"
#include "game.h"
#include "SceneClear.h"
#include "HowToStage.h"
#include "HowToPlayer.h"
#include <cassert>
#include <memory>

namespace
{
	// スタート時の遅延時間
	constexpr int kStartDelay = 300;
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;
}

SceneHowTo::SceneHowTo() :
	m_pHPlayer(std::make_shared<HowToPlayer>()),
	m_pHStage(std::make_shared<HowToStage>()),
	m_updateFunc(&SceneHowTo::SceneStartUpdate),
	m_hPlayer(-1),
	m_hPlayerWaveBurner(-1),
	m_hDeathEffect(-1),
	m_hObjectSpike(-1),
	m_hPortal(-1),
	m_hBlock(-1),
	m_hBg(-1),
	m_hDeathSound(-1),
	m_hPracBgm(-1),
	m_fadeCount(0),
	m_startDelay(0),
	m_startTextSize(0),
	m_gameOverDelay(0),
	m_isPrac(true),
	m_isEnd(false),
	m_pClear(nullptr)
{
}

SceneHowTo::~SceneHowTo()
{
}

// 初期化
void SceneHowTo::Init()
{
	// シーン終了変数を初期化
	m_isEnd = false;
	m_fadeCount = 255;
	m_updateFunc = &SceneHowTo::SceneStartUpdate;

	// アドレスの設定
	m_pHPlayer->SetStage(m_pHStage.get());
	m_pHStage->SetPlayer(m_pHPlayer.get());

	// 画像読み込み
	m_hPlayer = LoadGraph(Game::kPlayerImg);
	m_hPlayerWaveBurner = LoadGraph("imageData/AfterBurner.png");
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);
	m_hPortal = LoadGraph("imagedata/OrangePortal.png");
	m_hBlock = LoadGraph("imagedata/Tileset.png");
	m_hBg = LoadGraph("imagedata/GDbg.jpg");

	// 音データの読み込み
	m_hDeathSound = LoadSoundMem("soundData/deathSound.mp3");
	m_hPracBgm = LoadSoundMem("soundData/StayInsideMe.mp3");

	// スタート遅延の初期化
	m_startDelay = kStartDelay;
	m_startTextSize = 60;

	GameSetting();

	m_pHPlayer->SetSpawnPos(m_isPrac);
}

void SceneHowTo::GameSetting()
{
	// 各時間用変数の初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_pHPlayer->Init(m_hPlayer, m_hPlayerWaveBurner, m_hDeathEffect, m_hDeathSound, m_isPrac);

	// ステージ初期化
	m_pHStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock);
}

void SceneHowTo::PlayGameSound()
{
	if (!CheckSoundMem(m_hPracBgm)) PlaySoundMem(m_hPracBgm, DX_PLAYTYPE_BACK);
}

// 終了処理
void SceneHowTo::End()
{
	StopSoundMem(m_hPracBgm);

	// 画像データの削除
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hDeathEffect);
	DeleteGraph(m_hObjectSpike);
	DeleteGraph(m_hPortal);
	DeleteGraph(m_hBlock);
	DeleteGraph(m_hBg);

	DeleteSoundMem(m_hDeathSound);
	DeleteSoundMem(m_hPracBgm);
}

// 毎フレームの処理
void SceneHowTo::Update(const InputState& input, NextSceneState& nextScene)
{
	(this->*m_updateFunc)(input, nextScene);
}

// 毎フレームの描画
void SceneHowTo::Draw()
{
	m_pHStage->Draw();

	if (m_pHPlayer->IsStageClear()) return;

	// プレイヤーの描画
	m_pHPlayer->Draw();

	if (m_startDelay > 0)
	{
		if (m_startDelay % 60 == 0) m_startTextSize = 60;
		m_startTextSize--;
		if (m_startTextSize < 20) m_startTextSize = 20;

		SetFontSize(m_startTextSize);

		if (m_startDelay / 60 == 5)
		{
		}
		else if (m_startDelay / 60 == 0)
		{
			DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2), Game::kScreenHeightHalf, "GO!", 0xff2222);
		}
		else
		{
			DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2), Game::kScreenHeightHalf, 0xff2222, "%d", m_startDelay / 60);
		}
		SetFontSize(20);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneHowTo::OnStageClear(NextSceneState& nextScene)
{
	if (m_pHPlayer->IsStageClear())
	{
		if (m_pHStage->GetStageState() == HowToStageState::WaveTest)
		{
			nextScene = NextSceneState::nextClear;
			m_isEnd = true;
		}
		else
		{
			m_pHStage->SetNextStageState();
			GameSetting();
		}
	}
}

void SceneHowTo::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::escape))
	{
		nextScene = NextSceneState::nextMenu;
		m_isEnd = true;
	}

	// Rキーを押すとゲームリトライ
	if (input.IsTriggered(InputType::retry))
	{
		GameSetting();
		return;
	}

	if (input.IsTriggered(InputType::enter))
	{
		if (m_isPrac)
		{
			m_isPrac = false;
		}
		else
		{
			m_isPrac = true;
			m_pHStage->SetNextStageState();
		}

		GameSetting();
		return;
	}

	PlayGameSound();

	m_pHStage->Update();

	m_pHPlayer->Update(input);

	OnStageClear(nextScene);

	// プレイヤーの死亡判定が true の場合
	if (m_pHPlayer->IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			GameSetting();
			return;
		}
		// ゲームオーバー遅延を1フレームごとに減少させる
		m_gameOverDelay--;
		return;
	}
}

void SceneHowTo::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount -= 5;

	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneHowTo::NormalUpdate;
	}
}

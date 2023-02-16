#include "SceneMain.h"
#include "game.h"
#include "SceneClear.h"
#include "SceneRanking.h"
#include <cassert>

namespace
{
	// スタート時の遅延時間
	constexpr int kStartDelay = 300;
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;
}

SceneMain::SceneMain() :
	m_updateFunc(&SceneMain::SceneStartUpdate),
	m_hPlayer(-1),
	m_hPlayerWaveBurner(-1),
	m_hDeathEffect(-1),
	m_hObjectSpike(-1),
	m_hPortal(-1),
	m_hBlock(-1),
	m_hBg(-1), 
	m_hDeathSound(-1),
	m_hPracBgm(-1),
	m_hChallengeBgm(-1),
	m_hPlayBgm(-1),
	m_fadeCount(0),
	m_scroll(0),
	m_startDelay(0), 
	m_startTextSize(0),
	m_gameOverDelay(0),
	m_countAttempt(0),
	m_isPracticeMode(false),
	m_isEnd(false),
	m_selectedStage(StageState::firstStage),
	m_pManager(nullptr),
	m_pClear(nullptr),
	m_pRanking(nullptr)
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
	m_fadeCount = 255;
	m_updateFunc = &SceneMain::SceneStartUpdate;

	// アドレスの設定
	m_Player.SetStage(&m_Stage);
	m_Stage.SetPlayer(&m_Player);

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
	m_hChallengeBgm = LoadSoundMem("soundData/ElectromanAdventuresV2.mp3");

	if (m_isPracticeMode) m_hPlayBgm = m_hPracBgm;
	else m_hPlayBgm = m_hChallengeBgm;

	if (!m_isPracticeMode) m_Stage.SetFirstStage();
	else if (m_pClear->IsNextStage()) m_Stage.SetNextStageState();
	else m_Stage.SetSelectedStage(m_selectedStage);

	// スタート遅延の初期化
	m_startDelay = kStartDelay;
	m_startTextSize = 60;

	m_countAttempt = 1;

	GameSetting();
}

void SceneMain::GameSetting()
{	
	// 各時間用変数の初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_Player.Init(m_hPlayer, m_hPlayerWaveBurner,  m_hDeathEffect, m_hDeathSound);

	// ステージ初期化
	m_Stage.Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock);
}

void SceneMain::PlayGameSound()
{
	if(!CheckSoundMem(m_hPlayBgm)) PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK);
}

// 終了処理
void SceneMain::End()
{
	m_countAttempt = 0;
	StopSoundMem(m_hPlayBgm);

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
void SceneMain::Update(const InputState& input, NextSceneState& nextScene)
{		
	(this->*m_updateFunc)(input, nextScene);
}

// 毎フレームの描画
void SceneMain::Draw()
{
	m_Stage.Draw();

	if (m_Player.IsStageClear()) return;

	// プレイヤーの描画
	m_Player.Draw();
	
	DrawFormatString(10, 60, 0xffffff, "Attempt : %d", m_countAttempt);
	if(m_isPracticeMode) DrawString(10, 100, "pracmode", 0xff0000);

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

void SceneMain::OnStageClear(NextSceneState& nextScene)
{
	if (m_Player.IsStageClear())
	{
		if (m_Stage.GetStageState() == StageState::tenthStage || m_isPracticeMode)
		{
			if (!m_isPracticeMode)
			{
				m_pRanking->LoadRankingData();
				m_pRanking->SetRanking(m_countAttempt, m_Stage.GetStageState());
			}
			m_countAttempt = 1;
			nextScene = NextSceneState::nextClear;
			m_isEnd = true;
		}
		else
		{
			m_Stage.SetNextStageState();
			GameSetting();
		}
	}
}

void SceneMain::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::escape))
	{
		if (m_isPracticeMode) nextScene = NextSceneState::nextStageSelect;
		else nextScene = NextSceneState::nextMenu;
		m_isEnd = true;
	}

	// Rキーを押すとゲームリトライ
	if (input.IsTriggered(InputType::retry))
	{
		if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

		if (!m_isPracticeMode) m_Stage.SetFirstStage();
		GameSetting();
		m_countAttempt++;
		return;
	}

	m_startDelay--;
	if (m_startDelay > 0) return;
	else m_startDelay = 0;

	PlayGameSound();

	m_Stage.Update();

	m_Player.Update(input);

	OnStageClear(nextScene);

	// プレイヤーの死亡判定が true の場合
	if (m_Player.IsDead())
	{
		if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

		if (m_gameOverDelay < 0)
		{
			if (!m_isPracticeMode) m_Stage.SetFirstStage();
			GameSetting();
			m_countAttempt++;
			return;
		}
		// ゲームオーバー遅延を1フレームごとに減少させる
		m_gameOverDelay--;
		return;
	}
}

void SceneMain::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount -= 5;
	
	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneMain::NormalUpdate;
	}
}

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
	m_hPortal(-1),
	m_hBlock(-1),
	m_hBg(-1), 
	m_hDeathSound(-1),
	m_hPracBgm(-1),
	m_hChallengeBgm(-1),
	m_hPlayBgm(-1),
	m_scroll(0),
	m_startDelay(0),
	m_gameOverDelay(0),
	m_countAttempt(0),
	m_isPracticeMode(false),
	m_isEnd(false),
	m_selectedStage(StageState::firstStage),
	m_pManager(nullptr)
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
	else m_Stage.SetSelectedStage(m_selectedStage);

	// スタート遅延の初期化
	m_startDelay = kStartDelay;

	GameSetting();
}

void SceneMain::GameSetting()
{	
	// 各時間用変数の初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_Player.Init(m_playerHandle, m_deathEffectHandle, m_hDeathSound);

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
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_deathEffectHandle);
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
	if (input.IsTriggered(InputType::escape))
	{
		if(m_isPracticeMode) nextScene = NextSceneState::nextStageSelect;
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
		if(!m_isPracticeMode) StopSoundMem(m_hPlayBgm);
		
		if (m_gameOverDelay < 0)
		{
			if(!m_isPracticeMode) m_Stage.SetFirstStage();
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
	m_Stage.Draw();

	if (m_Player.IsStageClear()) return;

	// プレイヤーの描画
	m_Player.Draw();
	
	DrawFormatString(10, 60, 0xffffff, "Attempt : %d", m_countAttempt);
	if(m_isPracticeMode) DrawString(10, 100, "pracmode", 0xff0000);
}

void SceneMain::OnStageClear(NextSceneState& nextScene)
{
	if (m_Player.IsStageClear())
	{
		if (m_Stage.GetStageState() == StageState::tenthStage || m_isPracticeMode)
		{
			m_countAttempt = 0;
			m_Stage.SetNextStageState();
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

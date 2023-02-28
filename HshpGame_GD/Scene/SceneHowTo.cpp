#include "SceneHowTo.h"
#include "game.h"
#include "SceneClear.h"
#include "HowToStage.h"
#include "HowToPlayer.h"
#include <cassert>
#include <memory>
#include <string>

namespace
{
	// スタート時の遅延時間
	constexpr int kStartDelay = 0;
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;

	// オブジェクト名
	const char* const kNextStageText = "→ ENTER で下へ";
	const char* const kNextGimmickText = "→ ENTER で次へ";
	const char* const kJumpText = "SPACE or ↑ でジャンプ";
	const char* const kGimmickText = "SPACE or ↑ でギミック使用";
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
	m_hJumpPad(-1),
	m_hBg(-1),
	m_hTutoText(-1),
	m_hFontS(-1),
	m_hFontL(-1),
	m_hDeathSound(-1),
	m_hPracBgm(-1),
	m_fadeCount(0),
	m_countFrame(0),
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
void SceneHowTo::Init(int font24, int font48)
{
	m_hFontS = font24;
	m_hFontL = font48;
	
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
	m_hJumpPad = LoadGraph("imagedata/JumpPad.png");
	m_hBg = LoadGraph("imagedata/Bg.png");
	m_hTutoText = LoadGraph("imagedata/tutorialText.png");

	// 音データの読み込み
	m_hDeathSound = LoadSoundMem("soundData/deathSound.mp3");
	m_hPracBgm = LoadSoundMem("soundData/StayInsideMe.mp3");

	// スタート遅延の初期化
	m_startDelay = kStartDelay;
	m_startTextSize = 100;

	m_pHStage->SetFirstStage();

	OnGameStart();

	m_pHPlayer->SetSpawnPos(m_isPrac);
}

void SceneHowTo::OnGameStart()
{
	// 各時間用変数の初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_pHPlayer->Init(m_hPlayer, m_hPlayerWaveBurner, m_hDeathEffect, m_hDeathSound, m_isPrac);

	// ステージ初期化
	m_pHStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock, m_hJumpPad);
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
	DeleteGraph(m_hTutoText);

	DeleteSoundMem(m_hDeathSound);
	DeleteSoundMem(m_hPracBgm);
}

// 毎フレームの処理
void SceneHowTo::Update(const InputState& input, NextSceneState& nextScene)
{
	m_countFrame++;

	(this->*m_updateFunc)(input, nextScene);
}

// 毎フレームの描画
void SceneHowTo::Draw()
{
	m_pHStage->Draw();

	if (m_pHPlayer->IsStageClear()) return;

	// プレイヤーの描画
	m_pHPlayer->Draw();

	DrawHowTo();

	DrawGraph(0,0,m_hTutoText, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneHowTo::DrawHowTo()
{
	DrawBox(0, static_cast<int>(Game::kBlockSize * 11), Game::kScreenWidth, static_cast<int>(Game::kBlockSize * 13), 0x000000, true);
	
	int textDrawX = Game::kScreenWidthHalf + 250, textDrawY = Game::kScreenHeightHalf + 27;
	std::string drawTextMessage;

	if (m_isPrac)
	{
		drawTextMessage = kNextStageText;
	}
	else
	{
		drawTextMessage = kNextGimmickText;
	}
	
	if (m_countFrame > 900)
	{
		if ((m_countFrame / 10) % 4 != 0)
		{
			DrawFormatStringToHandle(textDrawX, textDrawY, 0xffffff, m_hFontS, "%s", drawTextMessage.c_str());
		}
	}
	else
	{
		DrawFormatStringToHandle(textDrawX, textDrawY, 0xffffff, m_hFontS, "%s", drawTextMessage.c_str());
	}


	if (m_pHStage->GetStageState() == HowToStageState::CubeTest)
	{
		drawTextMessage = kJumpText;
	}
	else
	{
		drawTextMessage = kGimmickText;
	}
	SetFontSize(60);

	textDrawX = Game::kScreenWidthHalf -(GetDrawStringWidth(drawTextMessage.c_str(), GetStringLength(drawTextMessage.c_str())) / 2);
	textDrawY = Game::kScreenHeightHalf + 15;
	DrawFormatStringToHandle(textDrawX, textDrawY, 0xffff00, m_hFontL, "%s", drawTextMessage.c_str());

	m_startTextSize--;
	if (m_startTextSize < 60) m_startTextSize = 60;

	SetFontSize(20);
}

void SceneHowTo::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::escape))
	{
		nextScene = NextSceneState::nextTitle;
		m_isEnd = true;
	}

	// Rキーを押すとゲームリトライ
	if (input.IsTriggered(InputType::retry))
	{
		OnGameStart();
		return;
	}

	m_startDelay--;
	if (m_startDelay > 0) return;
	else m_startDelay = 0;

	if (input.IsTriggered(InputType::enter))
	{
		m_countFrame = 0;
		
		if (m_pHStage->GetStageState() == HowToStageState::RevRingTest && !m_isPrac)
		{
			nextScene = NextSceneState::nextTitle;
			m_isEnd = true;
		}
		
		if (m_isPrac)
		{
			m_isPrac = false;
		}
		else
		{
			m_isPrac = true;
			m_pHStage->SetNextStageState();
		}

		OnGameStart();
		return;
	}

	PlayGameSound();

	m_pHStage->Update();

	m_pHPlayer->Update(input, m_isPrac);

	// プレイヤーの死亡判定が true の場合
	if (m_pHPlayer->IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			OnGameStart();
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

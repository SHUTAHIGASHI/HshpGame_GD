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
	// �X�^�[�g���̒x������
	constexpr int kStartDelay = 0;
	// ���S���̒x��
	constexpr int kGameOverDelay = 30;

	// �I�u�W�F�N�g��
	const char* const kNextStageText = "�� ENTER �ŉ���";
	const char* const kNextGimmickText = "�� ENTER �Ŏ���";
	const char* const kJumpText = "SPACE or �� �ŃW�����v";
	const char* const kGimmickText = "SPACE or �� �ŃM�~�b�N�g�p";
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

// ������
void SceneHowTo::Init(int font24, int font48)
{
	m_hFontS = font24;
	m_hFontL = font48;
	
	// �V�[���I���ϐ���������
	m_isEnd = false;
	m_fadeCount = 255;
	m_updateFunc = &SceneHowTo::SceneStartUpdate;

	// �A�h���X�̐ݒ�
	m_pHPlayer->SetStage(m_pHStage.get());
	m_pHStage->SetPlayer(m_pHPlayer.get());

	// �摜�ǂݍ���
	m_hPlayer = LoadGraph(Game::kPlayerImg);
	m_hPlayerWaveBurner = LoadGraph("imageData/AfterBurner.png");
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);
	m_hPortal = LoadGraph("imagedata/OrangePortal.png");
	m_hBlock = LoadGraph("imagedata/Tileset.png");
	m_hJumpPad = LoadGraph("imagedata/JumpPad.png");
	m_hBg = LoadGraph("imagedata/Bg.png");
	m_hTutoText = LoadGraph("imagedata/tutorialText.png");

	// ���f�[�^�̓ǂݍ���
	m_hDeathSound = LoadSoundMem("soundData/deathSound.mp3");
	m_hPracBgm = LoadSoundMem("soundData/StayInsideMe.mp3");

	// �X�^�[�g�x���̏�����
	m_startDelay = kStartDelay;
	m_startTextSize = 100;

	m_pHStage->SetFirstStage();

	OnGameStart();

	m_pHPlayer->SetSpawnPos(m_isPrac);
}

void SceneHowTo::OnGameStart()
{
	// �e���ԗp�ϐ��̏�����
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_pHPlayer->Init(m_hPlayer, m_hPlayerWaveBurner, m_hDeathEffect, m_hDeathSound, m_isPrac);

	// �X�e�[�W������
	m_pHStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock, m_hJumpPad);
}

void SceneHowTo::PlayGameSound()
{
	if (!CheckSoundMem(m_hPracBgm)) PlaySoundMem(m_hPracBgm, DX_PLAYTYPE_BACK);
}

// �I������
void SceneHowTo::End()
{
	StopSoundMem(m_hPracBgm);

	// �摜�f�[�^�̍폜
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

// ���t���[���̏���
void SceneHowTo::Update(const InputState& input, NextSceneState& nextScene)
{
	m_countFrame++;

	(this->*m_updateFunc)(input, nextScene);
}

// ���t���[���̕`��
void SceneHowTo::Draw()
{
	m_pHStage->Draw();

	if (m_pHPlayer->IsStageClear()) return;

	// �v���C���[�̕`��
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

	// R�L�[�������ƃQ�[�����g���C
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

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_pHPlayer->IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			OnGameStart();
			return;
		}
		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
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

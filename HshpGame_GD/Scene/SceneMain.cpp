#include "SceneMain.h"
#include "Player.h"
#include "Stage.h"
#include "game.h"
#include "SceneClear.h"
#include "SceneRanking.h"
#include <cassert>
#include <memory>

namespace
{
	// �X�^�[�g���̒x������
	constexpr int kStartDelay = 300;
	// �X�^�[�g�J�E���g�_�E���̕����T�C�Y
	constexpr int kStartTextSizeMax = 100;
	// ���S���̒x��
	constexpr int kGameOverDelay = 30;
}

SceneMain::SceneMain() :
	m_pPlayer(std::make_shared<Player>()),
	m_pStage(std::make_shared<Stage>()),
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

// ������
void SceneMain::Init()
{
	// �V�[���I���ϐ���������
	m_isEnd = false;
	m_fadeCount = 255;
	m_updateFunc = &SceneMain::SceneStartUpdate;

	// �A�h���X�̐ݒ�
	m_pPlayer->SetStage(m_pStage.get());
	m_pStage->SetPlayer(m_pPlayer.get());

	// �摜�ǂݍ���
	m_hPlayer = LoadGraph(Game::kPlayerImg);
	m_hPlayerWaveBurner = LoadGraph("imageData/AfterBurner.png");
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);
	m_hPortal = LoadGraph("imagedata/OrangePortal.png");
	m_hBlock = LoadGraph("imagedata/Tileset.png");
	m_hBg = LoadGraph("imagedata/GDbg.jpg");

	// ���f�[�^�̓ǂݍ���
	m_hDeathSound = LoadSoundMem("soundData/deathSound.mp3");
	m_hPracBgm = LoadSoundMem("soundData/StayInsideMe.mp3");
	m_hChallengeBgm = LoadSoundMem("soundData/ElectromanAdventuresV2.mp3");

	if (m_isPracticeMode) m_hPlayBgm = m_hPracBgm;
	else m_hPlayBgm = m_hChallengeBgm;

	if (!m_isPracticeMode) m_pStage->SetFirstStage();
	else if (m_selectedStage != StageState::End) m_pStage->SetSelectedStage(m_selectedStage);
	else if (m_pClear->IsNextStage()) m_pStage->SetNextStageState();
	else assert(0);

	// �X�^�[�g�x���̏�����
	m_startDelay = kStartDelay;
	m_startTextSize = kStartTextSizeMax;

	m_countAttempt = 1;

	OnGameStart();
}

void SceneMain::OnGameStart()
{	
	// �e���ԗp�ϐ��̏�����
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_pPlayer->Init(m_hPlayer, m_hPlayerWaveBurner,  m_hDeathEffect, m_hDeathSound);

	// �X�e�[�W������
	m_pStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock);
}

void SceneMain::PlayGameSound()
{
	if(!CheckSoundMem(m_hPlayBgm)) PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK);
}

// �I������
void SceneMain::End()
{
	m_selectedStage = StageState::End;

	m_countAttempt = 0;
	StopSoundMem(m_hPlayBgm);

	// �摜�f�[�^�̍폜
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hDeathEffect);
	DeleteGraph(m_hObjectSpike);
	DeleteGraph(m_hPortal);
	DeleteGraph(m_hBlock);
	DeleteGraph(m_hBg);

	DeleteSoundMem(m_hDeathSound);
	DeleteSoundMem(m_hPracBgm);
}

// ���t���[���̏���
void SceneMain::Update(const InputState& input, NextSceneState& nextScene)
{		
	(this->*m_updateFunc)(input, nextScene);
}

// ���t���[���̕`��
void SceneMain::Draw()
{
	m_pStage->Draw();

	if (m_pPlayer->IsStageClear()) return;

	// �v���C���[�̕`��
	m_pPlayer->Draw();
	
	DrawFormatString(10, 60, 0xffffff, "Attempt : %d", m_countAttempt);
	if(m_isPracticeMode) DrawString(10, 100, "pracmode", 0xff0000);

	if (m_startDelay > 0)
	{
		DrawStartCount();
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneMain::DrawStartCount()
{
	if (m_startDelay % 60 == 0) m_startTextSize = kStartTextSizeMax;
	m_startTextSize--;
	if (m_startTextSize < 60) m_startTextSize = 60;

	if (m_startDelay / 60 == 5)
	{
	}
	else if (m_startDelay / 60 == 0)
	{
		SetFontSize(m_startTextSize + 5);
		DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2), Game::kScreenHeightHalf, "GO!", 0xe9e9e9);
		SetFontSize(m_startTextSize);
		DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2), Game::kScreenHeightHalf, "GO!", 0xff2222);
	}
	else
	{
		SetFontSize(m_startTextSize + 5);
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2), Game::kScreenHeightHalf, 0xe9e9e9, "%d", m_startDelay / 60);
		SetFontSize(m_startTextSize);
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2), Game::kScreenHeightHalf, 0xff2222, "%d", m_startDelay / 60);
	}
	SetFontSize(20);
}

void SceneMain::OnStageClear(NextSceneState& nextScene)
{
	if (m_pPlayer->IsStageClear())
	{
		if (m_pStage->GetStageState() == StageState::tenthStage || m_isPracticeMode)
		{
			if (!m_isPracticeMode)
			{
				m_pRanking->LoadRankingData();
				m_pRanking->SetRanking(m_countAttempt, m_pStage->GetStageState());
			}
			m_countAttempt = 1;
			nextScene = NextSceneState::nextClear;
			m_isEnd = true;
		}
		else
		{
			m_pStage->SetNextStageState();
			OnGameStart();
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

	// R�L�[�������ƃQ�[�����g���C
	if (input.IsTriggered(InputType::retry))
	{
		if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

		if (!m_isPracticeMode) m_pStage->SetFirstStage();
		OnGameStart();
		m_countAttempt++;
		return;
	}

	m_startDelay--;
	if (m_startDelay > 0) return;
	else m_startDelay = 0;

	PlayGameSound();

	m_pStage->Update();

	m_pPlayer->Update(input);

	OnStageClear(nextScene);

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_pPlayer->IsDead())
	{
		if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

		if (m_gameOverDelay < 0)
		{
			if (!m_isPracticeMode) m_pStage->SetFirstStage();
			OnGameStart();
			m_countAttempt++;
			return;
		}
		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
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

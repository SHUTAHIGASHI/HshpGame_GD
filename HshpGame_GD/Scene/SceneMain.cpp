#include "SceneMain.h"
#include "game.h"
#include <cassert>

namespace
{
	// �X�^�[�g���̒x������
	constexpr int kStartDelay = 100;
	// ���S���̒x��
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

// ������
void SceneMain::Init()
{
	// �V�[���I���ϐ���������
	m_isEnd = false;

	// �A�h���X�̐ݒ�
	m_Player.SetStage(&m_Stage);
	m_Stage.SetPlayer(&m_Player);

	// �摜�ǂݍ���
	m_playerHandle = LoadGraph(Game::kPlayerImg);
	m_deathEffectHandle = LoadGraph(Game::kPlayerDeathEffectImg);
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

	if (!m_isPracticeMode) m_Stage.SetFirstStage();
	else m_Stage.SetSelectedStage(m_selectedStage);

	// �X�^�[�g�x���̏�����
	m_startDelay = kStartDelay;

	GameSetting();
}

void SceneMain::GameSetting()
{	
	// �e���ԗp�ϐ��̏�����
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_Player.Init(m_playerHandle, m_deathEffectHandle, m_hDeathSound);

	// �X�e�[�W������
	m_Stage.Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock);
}

void SceneMain::PlayGameSound()
{
	if(!CheckSoundMem(m_hPlayBgm)) PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK);
}

// �I������
void SceneMain::End()
{
	m_countAttempt = 0;
	StopSoundMem(m_hPlayBgm);

	// �摜�f�[�^�̍폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_deathEffectHandle);
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
	if (input.IsTriggered(InputType::escape))
	{
		if(m_isPracticeMode) nextScene = NextSceneState::nextStageSelect;
		else nextScene = NextSceneState::nextMenu;
		m_isEnd = true;
	}
	
	// R�L�[�������ƃQ�[�����g���C
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

	// �v���C���[�̎��S���肪 true �̏ꍇ
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
		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
		m_gameOverDelay--;
		return;
	}
}

// ���t���[���̕`��
void SceneMain::Draw()
{
	m_Stage.Draw();

	if (m_Player.IsStageClear()) return;

	// �v���C���[�̕`��
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

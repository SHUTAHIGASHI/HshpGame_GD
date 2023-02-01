#include "game.h"
#include "SceneMain.h"

#include <cassert>

namespace
{
	// �G�o���p�̒x������
	constexpr int kSpawnDelay = 100;
	// �Q�[���̐�������
	constexpr int kGameMaxTime = 1800;	
	// ���S���̒x��
	constexpr int kGameOverDelay = 30;

	// RGB�����l�p
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

// ������
void SceneMain::Init()
{
	// �A�h���X�̐ݒ�
	m_Player.SetStage(&m_Stage);
	m_Stage.SetPlayer(&m_Player);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);

	// �摜�ǂݍ���
	m_playerImg = LoadGraph(Game::kPlayerImg);
	m_deathEffectImg = LoadGraph(Game::kPlayerDeathEffectImg);

	GameSetting();
}

void SceneMain::GameSetting()
{
	// �V�[���I���A�Q�[���N���A�� false �ɏ�����
	m_isGameClear = false;
	m_isEnd = false;
	
	// �e���ԗp�ϐ��̏�����
	m_gameTimeRemaining = kGameMaxTime;
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_Player.Init(m_playerImg, m_deathEffectImg);

	// �X�e�[�W������
	m_Stage.Init(m_hObjectSpike);
}

// �I������
void SceneMain::End()
{
	// �摜�f�[�^�̍폜
	DeleteGraph(m_playerImg);
	DeleteGraph(m_deathEffectImg);
	DeleteGraph(m_hObjectSpike);
}

// ���t���[���̏���
void SceneMain::Update(const InputState& input)
{		
	if (input.IsTriggered(InputType::enter))
	{
		m_countAttempt = 0;
		m_isEnd = true;
	}
	
	// R�L�[�������ƃQ�[�����g���C
	if (input.IsTriggered(InputType::retry))
	{
		Init();
		m_countAttempt++;
	}

	m_Stage.Update();

	m_Player.Update(input);

	OnStageClear();

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_Player.IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			Init();
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

	// �v���C���[�̕`��
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

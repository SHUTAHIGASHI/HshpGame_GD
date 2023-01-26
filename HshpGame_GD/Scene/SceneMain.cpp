#include "game.h"
#include "SceneMain.h"

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
	m_countAttempt(0)
{
	m_hPlayerGraphic = -1;

	m_gameTimeRemaining = kGameMaxTime;
	m_gameOverDelay = kGameOverDelay;

	m_isGameClear = false;
	m_isEnd = false; 
}
SceneMain::~SceneMain()
{
}

// ������
void SceneMain::init()
{
	// �V�[���I���A�Q�[���N���A�� false �ɏ�����
	m_isGameClear = false;
	m_isEnd = false;

	// �A�h���X�̐ݒ�
	m_cPlayer.setStage(&m_Stage);
	m_Stage.setPlayer(&m_cPlayer);

	// �X�e�[�W������
	m_Stage.Init();

	// �摜�f�[�^�̓ǂݍ���
	m_hPlayerGraphic = LoadGraph("imagedata/PlayerCubeMini.png");
	// �v���C���[������ 
	m_cPlayer.Init(m_hPlayerGraphic);

	// �e���ԗp�ϐ��̏�����
	m_gameTimeRemaining = kGameMaxTime;
	m_gameOverDelay = kGameOverDelay;
}

// �I������
void SceneMain::end()
{
	// �摜�f�[�^�̍폜
	DeleteGraph(m_hPlayerGraphic);
}

// ���t���[���̏���
void SceneMain::update(const InputState& input)
{	
	if (input.IsTriggered(InputType::enter))
	{
		m_countAttempt = 0;
		m_isEnd = true;
	}
	
	// R�L�[�������ƃQ�[�����g���C
	if (input.IsTriggered(InputType::retry))
	{
		init();
		m_countAttempt++;
	}

	m_Stage.Update();

	// �v���C���[�̍X�V����
	m_cPlayer.Update(input);

	if (m_cPlayer.IsStageClear())
	{
		if (m_Stage.GetStageState() == StageState::firstStage)
		{
			m_Stage.SetSecondStage();
			m_Stage.Init();
			init();
		}
		else if (m_Stage.GetStageState() == StageState::secondStage)
		{
			m_countAttempt = 0;
			m_isGameClear = true;
			m_isEnd = true;
		}
	}

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_cPlayer.IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			init();
			m_countAttempt++;
			return;
		}
		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
		m_gameOverDelay--;
		return;
	}
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_Stage.Draw();

	// �v���C���[�̕`��
	m_cPlayer.Draw();
	
	DrawFormatString(10, 10, 0xffffff, "Attempt : %d", m_countAttempt);
}

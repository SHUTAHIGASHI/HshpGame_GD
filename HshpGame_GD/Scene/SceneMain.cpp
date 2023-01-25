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

	// �������ԕ\���ʒu
	constexpr int kTimerPositionX = Game::kScreenWidthHalf - 30;
	constexpr int kTimerPositionY = Game::kStageLowerLimit + 25;

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
	// �摜�f�[�^�̓ǂݍ���
	m_hPlayerGraphic = LoadGraph("imagedata/PlayerCubeMini.png");
	// �v���C���[������ 
	m_cPlayer.Init(m_hPlayerGraphic);
	m_cPlayer.setStage(&m_Stage);

	m_Stage.Init();
	m_Stage.setPlayer(&m_cPlayer);

	// �e���ԗp�ϐ��̏�����
	m_gameTimeRemaining = kGameMaxTime;
	m_gameOverDelay = kGameOverDelay;

	// �V�[���I���A�Q�[���N���A�� false �ɏ�����
	m_isGameClear = false;
	m_isEnd = false;
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

	if (m_cPlayer.IsGameClear())
	{
		m_countAttempt = 0;
		m_isGameClear = true;
		m_isEnd = true;
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

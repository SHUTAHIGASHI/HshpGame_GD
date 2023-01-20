#include "game.h"
#include "SceneMain.h"

namespace
{
	// �G�o���p�̒x������
	constexpr int kSpawnDelay = 100;
	// �Q�[���̐�������
	constexpr int kGameMaxTime = 1800;	
	// ���S���̒x��
	constexpr int kGameOverDelay = 90;

	// �������ԕ\���ʒu
	constexpr int kTimerPositionX = Game::kScreenWidthHalf - 30;
	constexpr int kTimerPositionY = Game::kStageLowerLimit + 25;

	// RGB�����l�p
	constexpr int kSetColor = 255;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;

	m_spawnDelay = 0;

	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

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

	// �e���ԗp�ϐ��̏�����
	m_spawnDelay = kSpawnDelay;
	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

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
	if (!m_gameTimeRemaining)	// �Q�[���c�莞�Ԃ�0�ɂȂ����ꍇ
	{
		//m_isGameClear = true;	// �Q�[���N���A�ƃV�[���I���� true �ɂ���
		//m_isEnd = true;			// �N���A�p�̃V�[���ֈڍs����
	}
	else if (!m_GameOverDelay)	// �Q�[���I�[�o�[�x����0�ɂȂ����ꍇ
	{
		m_isEnd = true;			// �V�[���I���݂̂� true �ɂ���			
	}							// �^�C�g���֖߂�

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_cPlayer.IsDead())
	{
		m_isEnd = true;
		
		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
		m_GameOverDelay--;
		return;
	}

	// 1�t���[�����ƂɎc�莞�ԂƓG�̏o���x��������������
	m_gameTimeRemaining--;
	m_spawnDelay--;

	// �o���x����0�ɂȂ����ꍇ�A�G���o��������
	if (!m_spawnDelay)
	{
		// �o���x���ɍĂђ萔����
		m_spawnDelay = kSpawnDelay;
	}

	m_Stage.Update();

	// �v���C���[�̍X�V����
	m_cPlayer.Update(input);
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_Stage.Draw();

	// �v���C���[�̕`��
	m_cPlayer.Draw();

	// �t�H���g�T�C�Y�ݒ�
	SetFontSize(Game::kFontSize);
	
	// �Q�[���̐������ԕ\�� (�ʏ�͔������A���v���Ԃ̔������߂���Ɖ��F�����A5�b���߂���Ɛԕ����ŕ\�������)
	int red = kSetColor;
	int green = kSetColor;
	int blue = kSetColor;
	if (m_gameTimeRemaining <= 300)
	{
		green = 0;
		blue = 0;
	}
	else if (m_gameTimeRemaining <= kGameMaxTime / 2)
	{
		green = 216;
		blue = 0;
	}
	DrawFormatString(kTimerPositionX, kTimerPositionY, GetColor(red, green, blue), "%d", m_gameTimeRemaining / 60);
}

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
	m_hBg(-1),
	m_hBgm(-1),
	m_scroll(0),
	m_startDelay(0),
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
	// �V�[���I���ϐ���������
	m_isEnd = false;

	// �A�h���X�̐ݒ�
	m_Player.SetStage(&m_Stage);
	m_Stage.SetPlayer(&m_Player);

	// �摜�ǂݍ���
	m_playerHandle = LoadGraph(Game::kPlayerImg);
	m_deathEffectHandle = LoadGraph(Game::kPlayerDeathEffectImg);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);
	m_hBg = LoadGraph("imagedata/bg.png");

	m_hBgm = LoadSoundMem("soundData/BACK ON TRACK_full.mp3");
	//PlaySoundMem(m_hBgm, DX_PLAYTYPE_BACK);

	// �X�^�[�g�x���̏�����
	m_startDelay = kStartDelay;

	GameSetting();
}

void SceneMain::GameSetting()
{
	// �Q�[���N���A��������
	m_isGameClear = false;
	
	// �e���ԗp�ϐ��̏�����
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_Player.Init(m_playerHandle, m_deathEffectHandle);

	// �X�e�[�W������
	m_Stage.Init(m_hObjectSpike, m_hBg);
}

// �I������
void SceneMain::End()
{
	// �摜�f�[�^�̍폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_deathEffectHandle);
	DeleteGraph(m_hObjectSpike);
	DeleteGraph(m_hBg);

	DeleteSoundMem(m_hBgm);
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
		GameSetting();
		m_countAttempt++;
	}

	m_startDelay--;
	if (m_startDelay > 0) return;
	else m_startDelay = 0;

	/*m_scroll++;
	if (m_scroll > Game::kScreenWidth) m_scroll = 0;*/

	m_Stage.Update();

	m_Player.Update(input);

	OnStageClear();

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_Player.IsDead())
	{
		if (m_gameOverDelay < 0)
		{
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
	/*int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/

	m_Stage.Draw();

	// �v���C���[�̕`��
	m_Player.Draw();
	
	DrawFormatString(10, 10, 0xffffff, "Attempt : %d", m_countAttempt);
}

void SceneMain::OnStageClear()
{
	if (m_Player.IsStageClear())
	{
		m_countAttempt = 0;

		if (m_Stage.GetStageState() == StageState::tenthStage)
		{
			m_Stage.ChangeStageState();
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

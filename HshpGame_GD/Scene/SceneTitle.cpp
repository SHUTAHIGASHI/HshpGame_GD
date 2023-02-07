#include "SceneTitle.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// �^�C�g�����b�Z�[�W
	const char* const kGameTitle = "GxxxxxxyDxxh";
	const char* const kTitleMessage = "ENTER to Start";

	// ���j���[���b�Z�[�W
	const char* const kStageSelectText = "StageSelect";
	const char* const kChallengeModeText = "ChallengeMode";
	const char* const kHelpText = "Help";
	const char* const kGameEndText = "Exit";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 4;

	// ���j���[�̃T�C�Y
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// ������
void SceneTitle::init()
{
	// �摜�f�[�^�̓ǂݍ���
	// �Q�[���^�C�g��
	m_hBackgroundGraphic = LoadGraph("imagedata/GDbg.jpg");

	// �e�L�X�g���W��������
	m_TextPosY = 0;
	m_TextVecY = 4;

	// �V�[���I���� false ����
	m_isEnd = false;
}

// �I������
void SceneTitle::end()
{
	DeleteGraph(m_hBackgroundGraphic);
}

// �X�V����
void SceneTitle::update(const InputState& input, bool &isGameEnd)
{	
	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		if (m_selectPos == 3)
		{
			isGameEnd = true;
			return;
		}
		m_isEnd = true;
	}

	if (input.IsTriggered(InputType::down))
	{
		m_selectPos++;
	}
	if (input.IsTriggered(InputType::up))
	{
		m_selectPos--;
	}
	
	if (m_selectPos > 3) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 3;
}

// �`�揈��
void SceneTitle::draw()
{
	// �w�i�摜��ǂݍ���ŕ\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hBackgroundGraphic, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(60);
	DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 6), Game::kScreenHeight / 4, kGameTitle, 0xffffff);
	SetFontSize(59);
	DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 6), Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(30);
	// �^�C�g���̃e�L�X�g��\��
	DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 7), Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	
	for (int i = 0; i < kMenuMax; i++)
	{
		DrawBox(menuX, menuY + (kMenuH * i)+ 10 , menuW, menuH + (kMenuH * i), 0xffffff, false);
	}

	DrawBox(menuX, menuY + (kMenuH * m_selectPos) + 10, menuW, menuH + (kMenuH * m_selectPos), 0xff0000, false);
}
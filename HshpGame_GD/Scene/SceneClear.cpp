#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// �^�C�g���\���܂ł̒x������ (2�b)
	constexpr int kTitleDelayMax = 120;

	// �e�L�X�g�T�C�Y
	constexpr int kTextSizeMin = 50;
	constexpr int kTextSizeMax = 70;

	// �e�L�X�g
	const char* const kGameClear = "Game Clear";

	// ���j���[���b�Z�[�W
	const char* const kRetryText = "Retry";
	const char* const kBackStageSelectText = "StageSelect";
	const char* const kBackTitleText = "TitleMenu";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 3;

	// ���j���[�̃T�C�Y
	constexpr int kLeftMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// ������
void SceneClear::Init()
{
	// �x�����ԏ�����
	m_sceneChangeDelay = kTitleDelayMax;

	m_textScale = kTextSizeMin;
	m_textScaleAcc = 1;
	
	m_isEnd = false;
}

// �I������
void SceneClear::End()
{
}

// �X�V
void SceneClear::Update(const InputState& input, NextSceneState& nextScene, const bool isPrac)
{
	if (m_textScale < kTextSizeMin) m_textScaleAcc *= -1;
	else if(m_textScale > kTextSizeMax) m_textScaleAcc *= -1;

	m_textScale += m_textScaleAcc;

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{
		case 0:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			return;
		case 1:
			m_isEnd = true;
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 2:
			m_isEnd = true;
			nextScene = NextSceneState::nextMenu;
			return;
		default:
			break;
		}
	}

	if (input.IsTriggered(InputType::down))
	{
		m_selectPos++;
	}
	if (input.IsTriggered(InputType::up))
	{
		m_selectPos--;
	}

	if (m_selectPos > 2) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 2;
}

void SceneClear::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 5), Game::kScreenHeight / 4, kGameClear, 0xffd700);
	SetFontSize(20);

	int menuX = kLeftMenuX, menuY = kMenuY, menuW = kLeftMenuX + kMenuW, menuH = kMenuY + kMenuH;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xffffff, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0) DrawString(menuX + 20, menuY, kRetryText, 0xffffff);
		if (i == 1) DrawString(menuX + 20, menuY, kBackStageSelectText, 0xffffff);
		if (i == 2) DrawString(menuX + 20, menuY, kBackTitleText, 0xffffff);
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0xff0000, false);
}
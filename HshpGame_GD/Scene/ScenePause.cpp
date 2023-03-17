#include "ScenePause.h"
#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include <string>

namespace
{
	// �^�C�g���\���܂ł̒x������ (2�b)
	constexpr int kTitleDelayMax = 120;

	// �e�L�X�g�T�C�Y
	constexpr int kTextSizeMin = 50;
	constexpr int kTextSizeMax = 80;

	// �e�L�X�g
	const char* const kGameClear = "Pause";
	const char* const kBackText = "����";

	// ���j���[���b�Z�[�W
	const char* const kRetryText = "���X�^�[�g";
	const char* const kBackStageSelectText = "�X�e�[�W�I����";
	const char* const kBackTitleText = "���j���[�ɖ߂�";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 3;

	// ���j���[�̃T�C�Y
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;
	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// ������
void ScenePause::Init(int fontS)
{
	m_updateFunc = &ScenePause::NormalUpdate;
	m_drawFunc = &ScenePause::NormalDraw;

	m_hPadImg = LoadGraph(Game::kPadImg);
	m_hSelectSound = LoadSoundMem(Game::kSelectSound);

	m_hFontS = fontS;

	m_textScale = kTextSizeMin;
	m_textScaleAcc = 1;
	m_selectPos = 0;

	m_isNextStage = false;
}

// �I������
void ScenePause::End()
{
	DeleteGraph(m_hPadImg);

	DeleteSoundMem(m_hSelectSound);
}

// �X�V
void ScenePause::Update(const InputState& input, NextSceneState& nextScene, bool& isEnd)
{
	m_textTimer++;

	(this->*m_updateFunc)(input, nextScene, isEnd);
}

void ScenePause::Draw()
{
	(this->*m_drawFunc)();
}

void ScenePause::DrawPadText()
{
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(25);
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 8 != 0)
		{
			int drawX = 100, drawY = Game::kScreenHeight - 80;
			// �^�C�g���̃e�L�X�g��\��
			DrawStringToHandle(drawX, drawY, kBackText, 0xe9e9e9, m_hFontS);

			int imgX, imgY, imgW, imgH;
			imgX = Game::kPadChipSize, imgY = Game::kPadChipSize * 11, imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;

			DrawRectExtendGraph(drawX - 50, drawY - 15, drawX, drawY + 35, imgX, imgY, imgW, imgH, m_hPadImg, true);
		}

		m_textTimer++;
	}
	SetFontSize(20);
}

void ScenePause::NormalUpdate(const InputState& input, NextSceneState& nextScene, bool& isPEnd)
{
	if (m_textScale > kTextSizeMax) m_textScaleAcc *= -1;
	else if (m_textScale < kTextSizeMin) m_textScaleAcc *= -1;
	m_textScale += m_textScaleAcc;

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		PlaySoundMem(m_hSelectSound, DX_PLAYTYPE_BACK);

		switch (m_selectPos)
		{
		case 0:
			m_pMain->OnRetry();
			return;
		case 1:
			isPEnd = true;
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 2:
			isPEnd = true;
			nextScene = NextSceneState::nextTitle;
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

void ScenePause::NormalDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2 + 3, Game::kScreenHeight / 4 + 5, kGameClear, 0x60CAAD);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xe9e9e9);
	SetFontSize(20);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xe9e9e9, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		if (i == 0) drawText = kRetryText;
		if (i == 1) drawText = kBackStageSelectText;
		if (i == 2) drawText = kBackTitleText;

		menuY = menuY + (kMenuH / 2) - 15;
		DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0x60CAAD, true);

	if (m_selectPos == 0) drawText = kRetryText;
	if (m_selectPos == 1) drawText = kBackStageSelectText;
	if (m_selectPos == 2) drawText = kBackTitleText;

	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatStringToHandle(menuX + 22, menuY + 5, 0x333333, m_hFontS, "%s", drawText.c_str());
	DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());

	DrawPadText();
}
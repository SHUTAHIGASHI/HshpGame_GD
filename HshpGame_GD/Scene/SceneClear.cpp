#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"
#include "SceneRanking.h"
#include <string>

namespace
{
	// �^�C�g���\���܂ł̒x������ (2�b)
	constexpr int kTitleDelayMax = 120;

	// �e�L�X�g�T�C�Y
	constexpr int kTextSizeMin = 30;
	constexpr int kTextSizeMax = 70;

	// �e�L�X�g
	const char* const kGameClear = "Game Clear";
	const char* const kRankin = "RankIn";

	// ���j���[���b�Z�[�W
	const char* const kNextText = "NextStage";
	const char* const kBackStageSelectText = "StageSelect";
	const char* const kBackTitleText = "TitleMenu";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 3;

	// ���j���[�̃T�C�Y
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;
	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// ������
void SceneClear::Init(int font)
{
	if (m_pRanking->IsRankIn())
	{
		m_updateFunc = &SceneClear::RankInUpdate;
		m_drawFunc = &SceneClear::RankInDraw;
	}
	else
	{
		m_updateFunc = &SceneClear::NormalUpdate;
		m_drawFunc = &SceneClear::NormalDraw;
	}

	m_hFont = font;

	// �x�����ԏ�����
	m_sceneChangeDelay = kTitleDelayMax;

	m_textScale = kTextSizeMin;
	m_textScaleAcc = 1;
	
	m_isEnd = false;
	m_isNextStage = false;
}

// �I������
void SceneClear::End()
{
}

// �X�V
void SceneClear::Update(const InputState& input, NextSceneState& nextScene, const bool isPrac)
{
	(this->*m_updateFunc)(input, nextScene, isPrac);
}

void SceneClear::Draw()
{
	(this->*m_drawFunc)();
}

void SceneClear::OnRankIn()
{
	
}

void SceneClear::NormalUpdate(const InputState& input, NextSceneState& nextScene, const bool isPrac)
{
	if (m_textScale > kTextSizeMax) m_textScaleAcc = 0;

	m_textScale += m_textScaleAcc;

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{
		case 0:
			m_isEnd = true;
			m_isNextStage = true;
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

void SceneClear::RankInUpdate(const InputState& input, NextSceneState& nextScene, const bool isPrac)
{
	if (m_textScale > kTextSizeMax) m_textScaleAcc = 0;

	m_textScale += m_textScaleAcc;
	char name[64];

	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectNamePos)
		{
		case 0:
			ChangeFont("����S�V�b�N");
			KeyInputString(Game::kScreenWidthHalf, Game::kScreenHeightHalf,
				64, name,
				true);
			m_name = name;
			ChangeFont("QuinqueFive");
			return;
		case 1:
			m_pRanking->SetPlayerName(m_name);
			m_pRanking->ResetRankIn();
			m_updateFunc = &SceneClear::NormalUpdate;
			m_drawFunc = &SceneClear::NormalDraw;
			return;
		default:
			break;
		}		
	}

	if (input.IsTriggered(InputType::down))
	{
		m_selectNamePos++;
	}
	if (input.IsTriggered(InputType::up))
	{
		m_selectNamePos--;
	}

	if (m_selectNamePos > 1) m_selectNamePos = 0;
	if (m_selectNamePos < 0) m_selectNamePos = 1;
}

void SceneClear::NormalDraw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale + 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xc0c0c0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xffd700);
	SetFontSize(20);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xffffff, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0) drawText = kNextText;
		if (i == 1) drawText = kBackStageSelectText;
		if (i == 2) drawText = kBackTitleText;

		DrawFormatString(menuX + 20, menuY, 0xffffff, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0xff0000, false);
}

void SceneClear::RankInDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale + 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kRankin, 6) / 2, Game::kScreenHeight / 4, kRankin, 0xc0c0c0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kRankin, 6) / 2, Game::kScreenHeight / 4, kRankin, 0xffd700);
	SetFontSize(20);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < 2; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xffffff, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0) drawText = "���O�̓��� / �ē���";
		if (i == 1) drawText = "���͂��I���";

		DrawFormatStringToHandle(menuX + 20, menuY, 0xffffff, m_hFont, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectNamePos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectNamePos), 0xff0000, false);

	DrawStringToHandle(Game::kScreenWidthHalf - GetDrawStringWidth(kRankin, 6) / 2, Game::kScreenHeight / 4, m_name.c_str(), 0xc0c0c0, m_hFont);
}

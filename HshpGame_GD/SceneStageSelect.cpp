#include "SceneStageSelect.h"
#include <DxLib.h>
#include "game.h"
#include "SceneMain.h"
#include "SceneManager.h"

namespace
{
	// �^�C�g�����b�Z�[�W
	const char* const kGameTitle = "Stage Select";
	const char* const kTitleMessage = "ENTER to Select";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 10;

	// ���j���[�̃T�C�Y
	constexpr int kLeftMenuX = Game::kScreenWidthHalf - 450;
	constexpr int kRightMenuX = Game::kScreenWidthHalf + 50;

	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// ������
void SceneStageSelect::Init()
{
	// �摜�f�[�^�̓ǂݍ���
	// �Q�[���^�C�g��
	m_hBg = LoadGraph("imagedata/GDbg.jpg");

	// �V�[���I���� false ����
	m_isEnd = false;

	m_textScroll = Game::kScreenWidth;
	m_selectPos = 0;
	m_textTimer = 10;
	m_scroll = 0;
	m_scrollAcc = 7;
	m_fadeCount = 0;

	m_scroll =  m_pTitle->GetScroll();

	m_updateFunc = &SceneStageSelect::SceneStartUpdate;
	if (m_pManager->GetLastScene() != SceneManager::kSceneTitle)
	{
		m_fadeCount = 255;
		m_textScroll = 0;
	}
}

// �I������
void SceneStageSelect::End()
{
	DeleteGraph(m_hBg);
}

// �X�V����
void SceneStageSelect::Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_textTimer > 1000) m_textTimer = 10;

	(this->*m_updateFunc)(input, isGameEnd, nextScene, isPrac);
}

// �`�揈��
void SceneStageSelect::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(60);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kTitleMessage, 6) + m_textScroll, Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 5 != 0)
		{
			// �^�C�g���̃e�L�X�g��\��
			DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 7) + m_textScroll, Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);
		}

		m_textTimer++;
	}

	int menuX = kLeftMenuX, menuY = kMenuY, menuW = kLeftMenuX + kMenuW, menuH = kMenuY + kMenuH;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;

		if (i > 4)
		{
			menuX = kRightMenuX, menuW = kRightMenuX + kMenuW;
			menuY = kMenuY + (kMenuH * (i - 5)) + 10;
		}

		DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuY + kMenuH - 10, 0xffffff, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		DrawFormatString(menuX + 20 + m_textScroll, menuY, 0xffffff, "Stage %d", i + 1);
	}

	menuX = kLeftMenuX, menuW = kLeftMenuX + kMenuW;
	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	if (m_selectPos > 4)
	{
		menuX = kRightMenuX, menuW = kRightMenuX + kMenuW;
		menuY = kMenuY + (kMenuH * (m_selectPos - 5)) + 10;
	}
	
	DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuY + kMenuH - 10, 0xff4500, true);

	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatString(menuX + 20 + m_textScroll, menuY, 0xffffff, "Stage %d", m_selectPos + 1);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneStageSelect::NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	m_scroll += m_scrollAcc;

	if (input.IsTriggered(InputType::escape))
	{
		nextScene = NextSceneState::nextMenu;
		m_updateFunc = &SceneStageSelect::SceneEndUpdate;
		return;
	}

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		m_updateFunc = &SceneStageSelect::SceneEndUpdate;

		switch (m_selectPos)
		{
		case 0:
			m_pMain->SetSelectedStage(StageState::firstStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 1:
			m_pMain->SetSelectedStage(StageState::secondStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 2:
			m_pMain->SetSelectedStage(StageState::thirdStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 3:
			m_pMain->SetSelectedStage(StageState::fourthStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 4:
			m_pMain->SetSelectedStage(StageState::fifthStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 5:
			m_pMain->SetSelectedStage(StageState::sixthStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 6:
			m_pMain->SetSelectedStage(StageState::seventhStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 7:
			m_pMain->SetSelectedStage(StageState::eighthStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 8:
			m_pMain->SetSelectedStage(StageState::ninthStage);
			nextScene = NextSceneState::nextGameMain;
			return;
		case 9:
			m_pMain->SetSelectedStage(StageState::tenthStage);
			nextScene = NextSceneState::nextGameMain;
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
	if (input.IsTriggered(InputType::right))
	{
		m_selectPos += 5;
		if (m_selectPos > 9)m_selectPos -= 10;
	}
	if (input.IsTriggered(InputType::left))
	{
		m_selectPos -= 5;
		if (m_selectPos < 0)m_selectPos += 10;
	}

	if (m_selectPos > 9) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 9;
}

void SceneStageSelect::SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	m_scroll += m_scrollAcc;

	if (m_pManager->GetLastScene() == SceneManager::kSceneTitle)
	{
		m_textScroll -= 100;

		if (m_textScroll < 0)
		{
			m_textScroll = 0;
			m_updateFunc = &SceneStageSelect::NormalUpdate;
		}
	}
	else
	{
		m_fadeCount -= 5;

		if (m_fadeCount < 0)
		{
			m_fadeCount = 0;
			m_updateFunc = &SceneStageSelect::NormalUpdate;
		}
	}
}

void SceneStageSelect::SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	if (nextScene == NextSceneState::nextMenu)
	{
		m_textScroll += 100;

		if (m_textScroll > Game::kScreenWidth)
		{
			m_isEnd = true;
		}
	}
	else
	{
		m_fadeCount += 5;

		if (m_fadeCount > 255)
		{
			m_isEnd = true;
		}
	}

	m_scroll += m_scrollAcc;
}
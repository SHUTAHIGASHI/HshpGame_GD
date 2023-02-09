#include "SceneStageSelect.h"
#include <DxLib.h>
#include "game.h"
#include "SceneMain.h"

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

	m_scrollAcc = -7;
}

// �I������
void SceneStageSelect::End()
{
	DeleteGraph(m_hBg);
}

// �X�V����
void SceneStageSelect::Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll < 0)
	{
		m_scroll = Game::kScreenWidth;
	}

	m_scroll += m_scrollAcc;

	if (input.IsTriggered(InputType::escape))
	{
		m_isEnd = true;
		nextScene = NextSceneState::nextMenu;
		return;
	}

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{
		case 0:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::firstStage);
			return;
		case 1:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::secondStage);
			return;
		case 2:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::thirdStage);
			return;
		case 3:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::fourthStage);
			return;
		case 4:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::fifthStage);
			return;
		case 5:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::sixthStage);
			return;
		case 6:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::seventhStage);
			return;
		case 7:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::eighthStage);
			return;
		case 8:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::ninthStage);
			return;
		case 9:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetSelectedStage(StageState::tenthStage);
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
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kTitleMessage, 6), Game::kScreenHeight / 4, kGameTitle, 0xffffff);
	SetFontSize(59);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kTitleMessage, 6), Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(30);
	// �^�C�g���̃e�L�X�g��\��
	DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 7), Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);

	int menuX = kLeftMenuX, menuY = kMenuY, menuW = kLeftMenuX + kMenuW, menuH = kMenuY + kMenuH;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;

		if (i > 4)
		{
			menuX = kRightMenuX, menuW = kRightMenuX + kMenuW;
			menuY = kMenuY + (kMenuH * (i - 5)) + 10;
		}

		DrawBox(menuX, menuY, menuW, menuY + kMenuH - 10, 0xffffff, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		DrawFormatString(menuX + 20, menuY, 0xffffff, "Stage %d", i + 1);
	}

	menuX = kLeftMenuX, menuW = kLeftMenuX + kMenuW;
	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	if (m_selectPos > 4)
	{
		menuX = kRightMenuX, menuW = kRightMenuX + kMenuW;
		menuY = kMenuY + (kMenuH * (m_selectPos - 5)) + 10;
	}
	
	DrawBox(menuX, menuY, menuW, menuY + kMenuH - 10, 0xff0000, false);
}
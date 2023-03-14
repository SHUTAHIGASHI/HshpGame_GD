#include "SceneRanking.h"
#include <DxLib.h>
#include "game.h"
#include "SceneMain.h"

namespace
{
	// �^�C�g�����b�Z�[�W
	const char* const kTextTitle = "Ranking";
	const char* const kTextBack = "Back";

	// ���j���[���b�Z�[�W
	const char* const kGameEndText = "Exit";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 10;

	// ���j���[�̃T�C�Y
	constexpr int kMenuX = Game::kScreenWidthHalf - 300;
	constexpr int kMenuY = Game::kScreenHeightHalf - 200;

	constexpr int kMenuW = 600;
	constexpr int kMenuH = 600;
}

// ������
void SceneRanking::Init(int font)
{	
	for (int i = 0; i < 10; i++) m_savedAttempt[i] = NULL;

	LoadRankingData();

	// �摜�f�[�^�̓ǂݍ���
	// �Q�[���^�C�g��
	m_hBg = LoadGraph(Game::kBgImg);
	m_hKeyimg = LoadGraph(Game::kPadImg);
	m_hBgm = LoadSoundMem("soundData/ranking.wav");
	m_hFont = font;
	// �V�[���I���� false ����
	m_isEnd = false;
	m_textTimer = 10;
	m_fadeCount = 255;

	m_updateFunc = &SceneRanking::SceneStartUpdate;
}

// �I������
void SceneRanking::End()
{
	SaveRankingData();

	DeleteGraph(m_hBg);
	DeleteGraph(m_hKeyimg);
	
	DeleteSoundMem(m_hBgm);
}

// �X�V����
void SceneRanking::Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (!CheckSoundMem(m_hBgm))
	{
		PlaySoundMem(m_hBgm, DX_PLAYTYPE_BACK);
	}

	if (m_textTimer > 1000) m_textTimer = 10;

	(this->*m_updateFunc)(input, isGameEnd, nextScene);
}

// �`�揈��
void SceneRanking::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(50);
	DrawString(Game::kScreenWidthHalf - (GetDrawStringWidth(kTextTitle, 7) / 2), Game::kScreenHeight / 6, kTextTitle, 0x60CAAD);
	DrawString(Game::kScreenWidthHalf - (GetDrawStringWidth(kTextTitle, 7) / 2), (Game::kScreenHeight / 6) + 5, kTextTitle, 0xe9e9e9);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(25);
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 4 != 0)
		{
			int drawX = 100, drawY = Game::kScreenHeight - 80;
			// �^�C�g���̃e�L�X�g��\��
			DrawString(drawX, drawY, kTextBack, 0xe9e9e9);

			int imgX, imgY, imgW, imgH;
			imgX = Game::kPadChipSize, imgY = Game::kPadChipSize * 12, imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;

			DrawRectExtendGraph(drawX - 50, drawY - 10, drawX, drawY + 40, imgX, imgY, imgW, imgH, m_hKeyimg, true);
		}

		m_textTimer++;
	}

	int menuX = kMenuX, menuY = kMenuY - 35, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;

	DrawBox(menuX, menuY, menuW, menuH, 0xe9e9e9, false);

	for (int i = 0; i < kMenuMax; i++)
	{
		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);
		int textColor = 0;
		menuY = kMenuY + (kMenuH / 10) * i;

		if (m_savedAttempt[i] == NULL)
		{
			textColor = 0xff0000;
			DrawFormatString(menuX + 20, menuY, textColor, "%02d . NoData", i + 1);
		}
		else
		{
			textColor = 0xffffff;
			DrawFormatString(menuX + 20, menuY, textColor, "%02d . attempt:%d", i + 1, m_savedAttempt[i]);
		}
	}

	SetFontSize(20);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneRanking::SetRanking(int attempt, StageState stage)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_savedAttempt[i] == NULL)
		{
			m_savedAttempt[i] = attempt;
			SaveRankingData();
			return;
		}

		if (m_savedAttempt[i] > attempt)
		{
			for (int j = 9; j > i; j--)
			{
				m_savedAttempt[j] = m_savedAttempt[j - 1];
			}
			m_savedAttempt[i] = attempt;

			SaveRankingData();
			return;
		}
	}
}

void SceneRanking::SaveRankingData()
{
	FILE* fp = nullptr;
	auto err = fopen_s(&fp, "ranking.info", "wb");
	if (fp == nullptr)
	{
		return;
	}

	fwrite(&m_savedAttempt, sizeof(m_savedAttempt), 1, fp);

	fclose(fp);
}

void SceneRanking::LoadRankingData()
{
	int handle = FileRead_open("ranking.info");

	if (handle == 0)
	{
		return;
	}

	FileRead_read(&m_savedAttempt, sizeof(m_savedAttempt), handle);

	FileRead_close(handle);
}

void SceneRanking::NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::back))
	{
		m_updateFunc = &SceneRanking::SceneEndUpdate;
		nextScene = NextSceneState::nextTitle;
		return;
	}
}

void SceneRanking::SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{	
	m_fadeCount -= 5;
	ChangeVolumeSoundMem(255 - m_fadeCount, m_hBgm);

	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneRanking::NormalUpdate;
	}
}

void SceneRanking::SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	m_fadeCount += 5;
	ChangeVolumeSoundMem(255 - m_fadeCount, m_hBgm);

	if (m_fadeCount > 255)
	{
		m_isEnd = true;
	}
}

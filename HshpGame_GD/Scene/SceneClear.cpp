#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "ParticleBase.h"
#include <string>

namespace
{
	// �^�C�g���\���܂ł̒x������ (2�b)
	constexpr int kTitleDelayMax = 120;

	// �e�L�X�g�T�C�Y
	constexpr int kTextSizeMin = 30;
	constexpr int kTextSizeMax = 90;

	constexpr int kTextFadeSpeed = 5;

	// �e�L�X�g
	const char* const kGameClear = "Game Clear";
	const char* const kStageClear = "StageClear";

	// ���j���[���b�Z�[�W
	const char* const kNextText = "���̃X�e�[�W��";
	const char* const kBackStageSelectText = "�X�e�[�W�I����";
	const char* const kBackTitleText = "���j���[�ɖ߂�";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 3;

	// ���j���[�̃T�C�Y
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;
	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;

	// �p�[�e�B�N���p
	constexpr int kAuraInterval = 2;
}

// ������
void SceneClear::Init(int fontS, int fontL)
{
	for (auto& pPart : particle)
	{
		pPart = std::make_shared<ParticleBase>();
	}
	auraFrame = kAuraInterval;

	if (m_pMain->GetStageState() == StageState::tenthStage)
	{
		OnAllClear();
	}
	else
	{
		m_updateFunc = &SceneClear::NormalUpdate;
		m_drawFunc = &SceneClear::NormalDraw;
	}

	m_hSelectSound = LoadSoundMem(Game::kSelectSound);

	m_hFontS = fontS;
	m_hFontL = fontL;

	// �x�����ԏ�����
	m_sceneChangeDelay = kTitleDelayMax;

	m_fadeCount = 0;

	m_shadowScale = kTextSizeMin;
	m_textFadeNum = 255;

	m_textScale = kTextSizeMin;
	m_textScaleAcc = 1;
	m_selectPos = 0;

	m_isEnd = false;
	m_isNextStage = false;
}

// �I������
void SceneClear::End()
{
	DeleteSoundMem(m_hSelectSound);
}

// �X�V
void SceneClear::Update(const InputState& input, NextSceneState& nextScene)
{
	ParticleUpdate();

	if (m_textScale > kTextSizeMax) m_textScaleAcc = 0;
	m_textScale += m_textScaleAcc;

	if (m_textFadeNum > 0)
	{
		m_shadowScale += kTextFadeSpeed;
		m_textFadeNum -= kTextFadeSpeed;
	}

	(this->*m_updateFunc)(input, nextScene);
}

void SceneClear::ParticleUpdate()
{
	sinRate += 0.20f;
	for (auto& pPart : particle)
	{
		if (!pPart->isExist())	continue;
		pPart->update();
	}

	auraFrame--;
	if (auraFrame <= 0)
	{
		int count = 0;
		for (auto& pPart : particle)
		{
			if (pPart->isExist())	continue;

			float randSin = static_cast<float>(GetRand(360)) / 360.0f;
			//randSin *= DX_TWO_PI_F;
			float randSpeed = static_cast<float>(GetRand(30)) / 10.0f + 1.0f;

			Vec2 pos;
			pos.x = static_cast<float>(GetRand(Game::kScreenWidth));
			pos.y = -150;// static_cast<float>(GetRand(Game::kScreenHeight));

			Vec2 vec;
			vec.x = cosf(randSin * DX_TWO_PI_F) * randSpeed;
			vec.y = sinf(randSin) * randSpeed;

			pPart->start(pos);
			pPart->setVec(vec);
			pPart->setRadius(4.0f);
			pPart->setColor(GetRandColor());
			pPart->setGravity(0.15f);
			pPart->setAlphaDec(1);
			pPart->setRadiusAcc(-0.02f);

			count++;
			if (count >= 32)
			{
				break;
			}
		}

		auraFrame = kAuraInterval;
	}
}

int SceneClear::GetRandColor()
{
	int tColorNum = 0;
	tColorNum = GetRand(6);

	switch (tColorNum)
	{
	case 0:
		return 0x00bfff;
	case 1:
		return 0xdc143c;
	case 2:
		return 0x9932cc;
	case 3:
		return 0xFFD700;
	case 4:
		return 0x80ff80;
	case 5:
		return 0x60CAAD;
	case 6:
		return 0xe9e9e9;
	default:
		break;
	}

	return 0xffffff;
}

void SceneClear::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int count = 0;
	for (auto& pPart : particle)
	{
		if (!pPart->isExist())	continue;
		pPart->draw();
		count++;
	}

	std::string clearText;
	if (m_pMain->GetStageState() == StageState::tenthStage) clearText = kGameClear;
	else clearText = kStageClear;

	if (m_textFadeNum > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_textFadeNum);
		SetFontSize(m_shadowScale);
		DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(clearText.c_str(), 10) / 2, Game::kScreenHeight / 4, clearText.c_str(), 0xe9e9e9);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �Q�[���N���A�e�L�X�g
	SetFontSize(m_textScale + 1);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(clearText.c_str(), 10) / 2, Game::kScreenHeight / 4, clearText.c_str(), 0xe9e9e9);
	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(clearText.c_str(), 10) / 2, Game::kScreenHeight / 4, clearText.c_str(), 0xffd733);
	SetFontSize(20);

	(this->*m_drawFunc)();

	// �t�F�[�h�����p�̏���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneClear::OnAllClear()
{
	m_updateFunc = &SceneClear::AllClearUpdate;
	m_drawFunc = &SceneClear::AllClearDraw;
}

void SceneClear::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		m_updateFunc = &SceneClear::SceneEndUpdate;
		PlaySoundMem(m_hSelectSound, DX_PLAYTYPE_BACK);

		switch (m_selectPos)
		{
		case 0:
			m_isNextStage = true;
			nextScene = NextSceneState::nextGameMain;
			return;
		case 1:
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 2:
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

void SceneClear::AllClearUpdate(const InputState& input, NextSceneState& nextScene)
{
	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		m_updateFunc = &SceneClear::SceneEndUpdate;

		switch (m_selectPos)
		{
		case 0:
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 1:
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

	if (m_selectPos > 1) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 1;
}

void SceneClear::SceneEndUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount += 5;
	ChangeVolumeSoundMem(255 - m_fadeCount, m_pMain->GetMusicHandle());

	if (m_fadeCount > 255)
	{
		m_isEnd = true;
	}
}

void SceneClear::NormalDraw()
{
	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xe9e9e9, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		if (i == 0) drawText = kNextText;
		if (i == 1) drawText = kBackStageSelectText;
		if (i == 2) drawText = kBackTitleText;

		menuY = menuY + (kMenuH / 2) - 15;
		DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0x60CAAD, true);

	if (m_selectPos == 0) drawText = kNextText;
	if (m_selectPos == 1) drawText = kBackStageSelectText;
	if (m_selectPos == 2) drawText = kBackTitleText;

	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatStringToHandle(menuX + 22, menuY + 5, 0x333333, m_hFontS, "%s", drawText.c_str());
	DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
}

void SceneClear::AllClearDraw()
{
	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < 2; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xe9e9e9, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		if (i == 0) drawText = kBackStageSelectText;
		if (i == 1) drawText = kBackTitleText;

		menuY = menuY + (kMenuH / 2) - 15;
		DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0x60CAAD, true);

	if (m_selectPos == 0) drawText = kBackStageSelectText;
	if (m_selectPos == 1) drawText = kBackTitleText;

	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatStringToHandle(menuX + 22, menuY + 5, 0x333333, m_hFontS, "%s", drawText.c_str());
	DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
}

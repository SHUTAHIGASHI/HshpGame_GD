#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// �^�C�g���\���܂ł̒x������ (2�b)
	constexpr int kTitleDelayMax = 120;

	// �e�L�X�g
	const char* const kGameClear = "Game Clear";
}

// ������
void SceneClear::Init()
{
	// �x�����ԏ�����
	sceneChangeDelay = kTitleDelayMax;
	
	m_isEnd = false;
}

// �I������
void SceneClear::End()
{
}

// �X�V
void SceneClear::Update(NextSceneState& nextScene, const bool isPrac)
{
	// 1�t���[�����ƂɎc��x�����Ԃ����炷
	sceneChangeDelay--;
	// 0�ɂȂ�����V�[���I��
	if (!sceneChangeDelay)
	{
		if (isPrac)
		{
			nextScene = NextSceneState::nextStageSelect;
			m_isEnd = true;
		}
		else
		{
			nextScene = NextSceneState::nextMenu;
			m_isEnd = true;
		}
	}
}

void SceneClear::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(60);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 5), Game::kScreenHeight / 4, kGameClear, 0xffffff);
	SetFontSize(59);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 5), Game::kScreenHeight / 4, kGameClear, 0xff4500);
}
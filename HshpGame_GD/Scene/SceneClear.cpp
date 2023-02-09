#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// タイトル表示までの遅延時間 (2秒)
	constexpr int kTitleDelayMax = 120;

	// テキスト
	const char* const kGameClear = "Game Clear";
}

// 初期化
void SceneClear::Init()
{
	// 遅延時間初期化
	sceneChangeDelay = kTitleDelayMax;
	
	m_isEnd = false;
}

// 終了処理
void SceneClear::End()
{
}

// 更新
void SceneClear::Update(NextSceneState& nextScene, const bool isPrac)
{
	// 1フレームごとに残り遅延時間を減らす
	sceneChangeDelay--;
	// 0になったらシーン終了
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
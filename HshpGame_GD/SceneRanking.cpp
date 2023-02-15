#include "SceneRanking.h"
#include <DxLib.h>
#include "game.h"
#include "SceneMain.h"

namespace
{
	// タイトルメッセージ
	const char* const kTextTitle = "Ranking";
	const char* const kTitleMessage = "ENTER to Select";

	// メニューメッセージ
	const char* const kGameEndText = "Exit";

	// メニューの選択項目の数
	constexpr int kMenuMax = 10;

	// メニューのサイズ
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// 初期化
void SceneRanking::Init()
{
	/*for (int i = 0; i < 10; i++)
	{
		m_savedAttempt[i] = 100;
	}*/
	
	// 画像データの読み込み
	// ゲームタイトル
	m_hBg = LoadGraph("imagedata/GDbg.jpg");
	// シーン終了に false を代入
	m_isEnd = false;
	m_selectPos = 0;
	m_textTimer = 10;
	m_fadeCount = 255;

	m_updateFunc = &SceneRanking::SceneStartUpdate;
}

// 終了処理
void SceneRanking::End()
{
	DeleteGraph(m_hBg);
}

// 更新処理
void SceneRanking::Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (m_textTimer > 1000) m_textTimer = 10;

	(this->*m_updateFunc)(input, isGameEnd, nextScene);
}

// 描画処理
void SceneRanking::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(50);
	DrawString(Game::kScreenWidthHalf - (GetDrawStringWidth(kTextTitle, 7) / 2), Game::kScreenHeight / 4, kTextTitle, 0xff4500);

	// フォントサイズの設定
	SetFontSize(20);
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 4 != 0)
		{
			// タイトルのテキストを表示
			DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 15) / 2, Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);
		}

		m_textTimer++;
	}

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xffffff, false);

		// フォントサイズの設定
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		DrawFormatString(menuX + 20, menuY, 0xffffff, "%d", m_savedAttempt[i]);
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0xff4500, true);

	menuY = menuY + (kMenuH / 2) - 15;

	DrawFormatString(menuX + 20, menuY, 0xffffff, "%d", m_savedAttempt[m_selectPos]);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneRanking::SetRanking(int attempt)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_savedAttempt[i] > attempt)
		{
			for (int j = 9; j > i; j--)
			{
				m_savedAttempt[j] = m_savedAttempt[j - 1];
			}
			m_savedAttempt[i] = attempt;
			return;
		}
	}
}

void SceneRanking::NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::escape))
	{
		m_updateFunc = &SceneRanking::SceneEndUpdate;
		nextScene = NextSceneState::nextMenu;
		return;
	}

	// キー入力があった場合、シーン終了を true にする
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{
		case 0:
			m_updateFunc = &SceneRanking::SceneEndUpdate;
			nextScene = NextSceneState::nextGameMain;
			return;
		case 1:
			m_updateFunc = &SceneRanking::SceneEndUpdate;
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 2:
			m_updateFunc = &SceneRanking::SceneEndUpdate;
			nextScene = NextSceneState::nextHelp;
			return;
		case 3:
			m_updateFunc = &SceneRanking::SceneEndUpdate;
			nextScene = NextSceneState::nextRanking;
			return;
		case 4:
			isGameEnd = true;
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

	if (m_selectPos > 9) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 9;
}

void SceneRanking::SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{	
	m_fadeCount -= 5;

	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneRanking::NormalUpdate;
	}
}

void SceneRanking::SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	m_fadeCount += 5;

	if (m_fadeCount > 255)
	{
		m_isEnd = true;
	}
}

#include "SceneTitle.h"
#include <DxLib.h>
#include "game.h"
#include "SceneManager.h"
#include "SceneMain.h"

namespace
{
	// タイトルメッセージ
	const char* const kGameTitle = "SquareJumper";
	const char* const kTitleMessage = "ENTER to Select";

	// メニューメッセージ
	const char* const kStageSelectText = "StageSelect";
	const char* const kChallengeModeText = "ChallengeMode";
	const char* const kHelpText = "How to Play";
	const char* const kRankText = "Ranking";
	const char* const kGameEndText = "Exit";

	// メニューの選択項目の数
	constexpr int kMenuMax = 5;

	// メニューのサイズ
	constexpr int kLeftMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// 初期化
void SceneTitle::Init()
{
	// 画像データの読み込み
	// ゲームタイトル
	m_hBg = LoadGraph("imagedata/GDbg.jpg");

	// シーン終了に false を代入
	m_isEnd = false;

	m_selectPos = 0;
	m_scrollAcc = 7;
}

// 終了処理
void SceneTitle::End()
{
	DeleteGraph(m_hBg);
}

// 更新処理
void SceneTitle::Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene, bool& isPrac)
{	
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	m_scroll += m_scrollAcc;

	// キー入力があった場合、シーン終了を true にする
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{		
		case 0:
			m_isEnd = true;
			nextScene = NextSceneState::nextGameMain;
			isPrac = false;
			return;
		case 1:
			m_isEnd = true;
			nextScene = NextSceneState::nextStageSelect;
			isPrac = true;
			return;
		case 2:
			m_isEnd = true;
			nextScene = NextSceneState::nextHelp;
			return;
		case 3:
			m_isEnd = true;
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
	
	if (m_selectPos > 4) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 4;
}

// 描画処理
void SceneTitle::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(60);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameTitle, 6), Game::kScreenHeight / 4, kGameTitle, 0xffffff);
	SetFontSize(59);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameTitle, 6), Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// フォントサイズの設定
	SetFontSize(30);
	// タイトルのテキストを表示
	DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 7), Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);

	int menuX = kLeftMenuX, menuY = kMenuY, menuW = kLeftMenuX + kMenuW, menuH = kMenuY + kMenuH;
	
	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xffffff, false);

		// フォントサイズの設定
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0) DrawString(menuX + 20, menuY, kChallengeModeText, 0xffffff);
		if (i == 1) DrawString(menuX + 20, menuY, kStageSelectText, 0xffffff);
		if (i == 2) DrawString(menuX + 20, menuY, kHelpText, 0xffffff);
		if (i == 3) DrawString(menuX + 20, menuY, kRankText, 0xffffff);
		if (i == 4) DrawString(menuX + 20, menuY, kGameEndText, 0xffffff);
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0xff0000, false);
}
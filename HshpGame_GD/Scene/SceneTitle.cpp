#include "SceneTitle.h"
#include <DxLib.h>
#include "game.h"
#include "SceneManager.h"
#include "SceneMain.h"

namespace
{
	// タイトルメッセージ
	const char* const kGameTitle = "SquareJumper";
	const char* const kTitleMessage = "ENTER to Start";

	// メニューメッセージ
	const char* const kStageSelectText = "StageSelect";
	const char* const kChallengeModeText = "ChallengeMode";
	const char* const kHelpText = "Help";
	const char* const kGameEndText = "Exit";

	// メニューの選択項目の数
	constexpr int kMenuMax = 5;

	// メニューのサイズ
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// 初期化
void SceneTitle::init()
{
	// 画像データの読み込み
	// ゲームタイトル
	m_hBackgroundGraphic = LoadGraph("imagedata/GDbg.jpg");

	// テキスト座標を初期化
	m_TextPosY = 0;
	m_TextVecY = 4;

	// シーン終了に false を代入
	m_isEnd = false;
}

// 終了処理
void SceneTitle::end()
{
	DeleteGraph(m_hBackgroundGraphic);
}

// 更新処理
void SceneTitle::update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene, bool& isPrac)
{	
	// キー入力があった場合、シーン終了を true にする
	if (input.IsTriggered(InputType::enter))
	{
		m_isEnd = true;

		switch (m_selectPos)
		{		
		case 0:
			nextScene = NextSceneState::nextGameMain;
			isPrac = false;
			return;
		case 1:
			nextScene = NextSceneState::nextGameMain;
			isPrac = true;
			return;
		case 2:
			nextScene = NextSceneState::nextHelp;
			return;
		case 3:
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
void SceneTitle::draw()
{
	// 背景画像を読み込んで表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hBackgroundGraphic, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(60);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kTitleMessage, 6), Game::kScreenHeight / 4, kGameTitle, 0xffffff);
	SetFontSize(59);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kTitleMessage, 6), Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// フォントサイズの設定
	SetFontSize(30);
	// タイトルのテキストを表示
	DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 7), Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	
	for (int i = 0; i < kMenuMax; i++)
	{
		DrawBox(menuX, menuY + (kMenuH * i)+ 10 , menuW, menuH + (kMenuH * i), 0xffffff, false);
	}

	DrawBox(menuX, menuY + (kMenuH * m_selectPos) + 10, menuW, menuH + (kMenuH * m_selectPos), 0xff0000, false);
}
#include "SceneStageSelect.h"
#include <DxLib.h>
#include "game.h"
#include "SceneMain.h"
#include "SceneManager.h"

namespace
{
	// タイトルメッセージ
	const char* const kGameTitle = "Stage Select";
	const char* const kTitleMessage = "ENTER to Select";

	// メニューの選択項目の数
	constexpr int kMenuMax = 10;

	// メニューのサイズ
	constexpr int kMenuX = Game::kScreenWidthHalf - 450;
	constexpr int kRightMenuX = Game::kScreenWidthHalf + 50;

	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// 初期化
void SceneStageSelect::Init()
{
	// 画像データの読み込み
	// ゲームタイトル
	m_hBg = LoadGraph("imagedata/GDbg.jpg");

	// シーン終了に false を代入
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

// 終了処理
void SceneStageSelect::End()
{
	DeleteGraph(m_hBg);
}

// 更新処理
void SceneStageSelect::Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_textTimer > 1000) m_textTimer = 10;

	(this->*m_updateFunc)(input, isGameEnd, nextScene, isPrac);
}

// 描画処理
void SceneStageSelect::Draw()
{
	// 背景描画処理
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// シーン名描画
	SetFontSize(60);
	DrawString((Game::kScreenWidth / 2) - (GetDrawStringWidth(kTitleMessage, 12) / 2) + m_textScroll, Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// ボタン用メッセージ
	SetFontSize(20);	// フォントサイズの設定
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 5 != 0)
		{
			// タイトルのテキストを表示
			DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 15) / 2 + m_textScroll, Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);
		}

		m_textTimer++;
	}

	// 選択枠の描画
	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;

		// 右側にずらす処理
		if (i > 4)
		{
			menuX = kRightMenuX, menuW = kRightMenuX + kMenuW;
			menuY = kMenuY + (kMenuH * (i - 5)) + 10;
		}

		// 枠の描画
		DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuY + kMenuH - 10, 0xffffff, false);

		// フォントサイズの設定
		SetFontSize(20);

		// 枠内の文字描画
		menuY = menuY + (kMenuH / 2) - 15;
		DrawFormatString(menuX + 20 + m_textScroll, menuY, 0xffffff, "Stage %d", i + 1);
	}

	// 現在選択中の枠の描画
	menuX = kMenuX, menuW = kMenuX + kMenuW;
	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	if (m_selectPos > 4)
	{
		menuX = kRightMenuX, menuW = kRightMenuX + kMenuW;
		menuY = kMenuY + (kMenuH * (m_selectPos - 5)) + 10;
	}
	
	// 選択中の枠の描画
	DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuY + kMenuH - 10, 0xff4500, true);

	// 選択中の枠内の文字描画
	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatString(menuX + 20 + m_textScroll, menuY, 0xffffff, "Stage %d", m_selectPos + 1);

	// フェード処理用
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

	// キー入力があった場合、シーン終了を true にする
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
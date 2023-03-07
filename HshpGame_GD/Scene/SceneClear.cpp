#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"
#include "SceneRanking.h"
#include "ParticleBase.h"
#include <string>

namespace
{
	// タイトル表示までの遅延時間 (2秒)
	constexpr int kTitleDelayMax = 120;

	// テキストサイズ
	constexpr int kTextSizeMin = 30;
	constexpr int kTextSizeMax = 90;

	constexpr int kTextFadeSpeed = 5;

	// テキスト
	const char* const kGameClear = "Game Clear";
	const char* const kRankin = "RankIn";

	// メニューメッセージ
	const char* const kNextText = "NextStage";
	const char* const kBackStageSelectText = "StageSelect";
	const char* const kBackTitleText = "TitleMenu";

	// メニューの選択項目の数
	constexpr int kMenuMax = 3;

	// メニューのサイズ
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;
	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;

	// パーティクル用
	constexpr int kAuraInterval = 2;
}

// 初期化
void SceneClear::Init(int font)
{
	for (auto& pPart : particle)
	{
		pPart = std::make_shared<ParticleBase>();
	}
	auraFrame = kAuraInterval;

	m_updateFunc = &SceneClear::NormalUpdate;
	m_drawFunc = &SceneClear::NormalDraw;

	m_hFont = font;

	// 遅延時間初期化
	m_sceneChangeDelay = kTitleDelayMax;

	m_shadowScale = kTextSizeMin;
	m_textFadeNum = 255;

	m_textScale = kTextSizeMin;
	m_textScaleAcc = 1;
	m_selectPos = 0;

	m_isEnd = false;
	m_isNextStage = false;
}

// 終了処理
void SceneClear::End()
{
}

// 更新
void SceneClear::Update(const InputState& input, NextSceneState& nextScene, const bool isPrac)
{
	sinRate += 0.20f;
	for (auto& pPart : particle)
	{
		if (!pPart->isExist())	continue;
		pPart->update();
	}

	ParticleUpdate();

	(this->*m_updateFunc)(input, nextScene, isPrac);
}

void SceneClear::ParticleUpdate()
{
	if (auraFrame <= 0)
	{
		int count = 0;
		for (auto& pPart : particle)
		{
			if (pPart->isExist())	continue;

			float randSin = static_cast<float>(GetRand(360)) / 360.0f;
			randSin *= DX_TWO_PI_F;
			float randSpeed = static_cast<float>(GetRand(60)) / 10.0f + 1.0f;

			Vec2 pos;
			//float dist = static_cast<float>(128 + GetRand(32));
			pos.x = static_cast<float>(GetRand(Game::kScreenWidth));//256 * 3 + cosf(randSin) * dist;
			pos.y = static_cast<float>(GetRand(Game::kScreenHeight));//512 + sinf(randSin) * dist;

			Vec2 vec;
			vec.x = cosf(randSin) * randSpeed;
			vec.y = sinf(randSin) * randSpeed;

			pPart->start(pos);
			pPart->setVec(vec);
			pPart->setRadius(4.0f);
			pPart->setColor(0x80ff80);
			pPart->setGravity(0.1f);
			pPart->setAlphaDec(8);
			pPart->setRadiusAcc(-0.05f);

			count++;
			if (count >= 32)
			{
				break;
			}
		}

		auraFrame = kAuraInterval;
	}
}

void SceneClear::Draw()
{
	int count = 0;
	for (auto& pPart : particle)
	{
		if (!pPart->isExist())	continue;
		pPart->draw();
		count++;
	}

	(this->*m_drawFunc)();
}

void SceneClear::NormalUpdate(const InputState& input, NextSceneState& nextScene, const bool isPrac)
{
	if (m_textScale > kTextSizeMax) m_textScaleAcc = 0;
	m_textScale += m_textScaleAcc;

	if (m_textFadeNum > 0)
	{
		m_shadowScale += kTextFadeSpeed;
		m_textFadeNum -= kTextFadeSpeed;
	}

	// キー入力があった場合、シーン終了を true にする
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{
		case 0:
			m_isEnd = true;
			m_isNextStage = true;
			nextScene = NextSceneState::nextGameMain;
			return;
		case 1:
			m_isEnd = true;
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 2:
			m_isEnd = true;
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

void SceneClear::NormalDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	if (m_textFadeNum > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_textFadeNum);
		SetFontSize(m_shadowScale);
		DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xe9e9e9);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ゲームクリアテキスト
	SetFontSize(m_textScale + 1);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xe9e9e9);
	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xffd733);
	SetFontSize(20);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xe9e9e9, false);

		// フォントサイズの設定
		SetFontSize(20);

		if (i == 0) drawText = kNextText;
		if (i == 1) drawText = kBackStageSelectText;
		if (i == 2) drawText = kBackTitleText;

		menuY = menuY + (kMenuH / 2) - 15;
		DrawFormatString(menuX + 20, menuY, 0xe9e9e9, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0x60CAAD, true);

	if (m_selectPos == 0) drawText = kNextText;
	if (m_selectPos == 1) drawText = kBackStageSelectText;
	if (m_selectPos == 2) drawText = kBackTitleText;

	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatString(menuX + 22, menuY + 5, 0x333333, "%s", drawText.c_str());
	DrawFormatString(menuX + 20, menuY, 0xe9e9e9, "%s", drawText.c_str());
}
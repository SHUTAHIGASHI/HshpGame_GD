#include "SceneClear.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// タイトル表示までの遅延時間 (2秒)
	constexpr int kTitleDelayMax = 120;
}

// 初期化
void SceneClear::init()
{
	// 遅延時間初期化
	titleDelay = kTitleDelayMax;
	
	m_isEnd = false;

	// 画像サイズの取得
	//GetGraphSize(m_hClearTextGraphic, &m_width, &m_height);
}

// 終了処理
void SceneClear::end()
{
	// 画像データの削除
	//DeleteGraph(m_hClearTextGraphic);
	//DeleteGraph(m_hBackgroundGraphic);
}

// 更新
void SceneClear::update()
{
	// 1フレームごとに残り遅延時間を減らす
	titleDelay--;
	// 0になったらシーン終了
	if (!titleDelay)
	{
		m_isEnd = true;
	}
}

void SceneClear::draw()
{
	// 背景画像の描画
	//DrawGraph(0, 0, m_hBackgroundGraphic, true);

	DrawString(Game::kScreenWidthHalf, Game::kScreenHeightHalf, "ステージクリア", 0xffffff);
}
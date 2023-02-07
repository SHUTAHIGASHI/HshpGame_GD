#pragma once
#include "SceneBase.h"
#include "InputState.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle():
		m_selectPos(0)
	{
		m_TextPosY = 0;
		m_TextVecY = 0;

		m_isEnd = false;

		m_hBackgroundGraphic = -1;
	}
	virtual ~SceneTitle() {}

	// 初期化
	virtual void init();
	
	// 終了処理
	void end();

	// 更新処理
	virtual void update(const InputState& input, bool &isGameEnd);
	// 描画
	virtual void draw();

	// m_isEnd を取得
	virtual bool isEnd() { return m_isEnd; }
private:	
	// メニュー選択
	int m_selectPos;
	
	// テキスト表示位置変更
	int m_TextPosY;
	int m_TextVecY;

	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hBackgroundGraphic;
};
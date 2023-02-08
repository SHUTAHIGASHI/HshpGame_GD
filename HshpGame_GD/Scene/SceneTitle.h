#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;

class SceneTitle : public SceneBase
{
public:
	SceneTitle():
		m_selectPos(0),
		m_TextPosY(0),
		m_TextVecY(0),
		m_isEnd(false),
		m_hBackgroundGraphic(-1)
	{
	}
	virtual ~SceneTitle() {}

	// 初期化
	virtual void Init();
	
	// 終了処理
	void End();

	// 更新処理
	void Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene, bool &isPrac);
	// 描画
	void Draw();

	// m_isEnd を取得
	bool IsEnd() const { return m_isEnd; }
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
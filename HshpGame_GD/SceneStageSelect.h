#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect() :
		m_selectPos(0),
		m_isEnd(false),
		m_hBg(-1),
		m_scroll(0),
		m_scrollAcc(0),
		m_pMain(nullptr)
	{
	}
	virtual ~SceneStageSelect() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// 初期化
	virtual void Init();

	// 終了処理
	void End();

	// 更新処理
	void Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
	// 描画
	void Draw();

	// m_isEnd を取得
	bool IsEnd() const { return m_isEnd; }
private:
	// メニュー選択
	int m_selectPos;

	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hBg;

	int m_scroll;
	int m_scrollAcc;

	SceneMain* m_pMain;
};
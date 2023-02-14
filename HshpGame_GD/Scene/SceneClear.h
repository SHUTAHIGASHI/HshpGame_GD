#pragma once
#include "SceneBase.h"
#include "game.h"

class SceneClear : public SceneBase
{
public:
	SceneClear():
		m_selectPos(0),
		m_sceneChangeDelay(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_isEnd(false)
	{
	}
	virtual ~SceneClear() {}

	// 初期化
	virtual void Init();
	
	// 終了処理
	void End();
	// 更新
	virtual void Update(const InputState& input, NextSceneState& nextScene, const bool isPrac);
	// 描画
	virtual void Draw();

	bool IsNextStage() const { return m_isNextStage; }

	// m_isEnd を取得
	virtual bool IsEnd() { return m_isEnd; }
private:
	// メニュー選択
	int m_selectPos;
	
	// タイトル表示までの遅延用変数
	int m_sceneChangeDelay;
	
	int m_textScale;
	int m_textScaleAcc;

	// 次のステージ
	bool m_isNextStage;
	// シーン終了
	bool m_isEnd;
};
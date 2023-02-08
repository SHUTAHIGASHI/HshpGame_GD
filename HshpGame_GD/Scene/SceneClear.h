#pragma once
#include "SceneBase.h"
#include "game.h"

class SceneClear : public SceneBase
{
public:
	SceneClear()
	{
		titleDelay = 0;
		
		m_isEnd = false;

		m_width = 0;
		m_height = 0;
	}
	virtual ~SceneClear() {}

	// 初期化
	virtual void Init();
	
	// 終了処理
	void end();
	// 更新
	virtual void Update(NextSceneState& nextScene);
	// 描画
	virtual void Draw();

	// m_isEnd を取得
	virtual bool IsEnd() { return m_isEnd; }
private:
	// タイトル表示までの遅延用変数
	int titleDelay;
	
	// シーン終了
	bool m_isEnd;

	// 画像サイズ
	int m_width;
	int m_height;
};
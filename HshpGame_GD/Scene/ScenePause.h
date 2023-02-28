#pragma once
#include "SceneBase.h"
#include "game.h"
#include <string>

class SceneMain;

class ScenePause : public SceneBase
{
public:
	ScenePause() :
		m_selectPos(0),
		m_selectNamePos(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_pMain(nullptr)
	{
	}
	virtual ~ScenePause() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// 初期化
	void Init();

	// 終了処理
	void End();
	// 更新
	virtual void Update(const InputState& input, NextSceneState& nextScene, bool &isEnd);
	// 描画
	virtual void Draw();

private:
	// Update
	using m_tUpdateFunc = void (ScenePause::*) (const InputState& input, NextSceneState& nextScene, bool& isEnd);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene, bool& isEnd);

	// Draw
	using m_tDrawFunc = void (ScenePause::*) ();
	m_tDrawFunc m_drawFunc = nullptr;

	void NormalDraw();
private:
	// メニュー選択
	int m_selectPos;
	int m_selectNamePos;

	int m_textScale;
	int m_textScaleAcc;

	// 次のステージ
	bool m_isNextStage;

	SceneMain* m_pMain;
};
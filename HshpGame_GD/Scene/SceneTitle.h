#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;
class SceneManager;
class SceneStageSelect;

class SceneTitle : public SceneBase
{
public:
	SceneTitle() :
		m_updateFunc(&SceneTitle::SceneStartUpdate),
		m_selectPos(0),
		m_textTimer(0),
		m_fadeCount(0),
		m_isEnd(false),
		m_hBg(LoadGraph("imagedata/Bg.png")),
		m_hLoopBgm(LoadSoundMem("soundData/MenuLoop.mp3")),
		m_textScroll(0),
		m_scroll(0),
		m_scrollAcc(0),
		m_pManager(nullptr),
		m_pStageSelect(nullptr)
	{
	}
	virtual ~SceneTitle() 
	{
		DeleteGraph(m_hBg);
		DeleteSoundMem(m_hLoopBgm);
	}

	void SetManager(SceneManager* manager) { m_pManager = manager; }
	void SetStageSelect(SceneStageSelect* stageSelect) { m_pStageSelect = stageSelect; }

	// 初期化
	virtual void Init();
	
	// 終了処理
	void End();

	// 更新処理
	void Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene, bool &isPrac);
	// 描画
	void Draw();

	void StopMusic();

	// m_isEnd を取得
	bool IsEnd() const { return m_isEnd; }

	int GetMusicHandle()const { return m_hLoopBgm; }
	int GetScroll()const { return m_scroll; }
private:
	using m_tUpdateFunc = void (SceneTitle::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);

	void SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);

	void SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
private:	
	// メニュー選択
	int m_selectPos;

	int m_textTimer;

	int m_fadeCount;
	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hBg;
	int m_hLoopBgm;

	int m_textScroll;

	int m_scroll;
	int m_scrollAcc;

	SceneManager* m_pManager;
	SceneStageSelect* m_pStageSelect;
};
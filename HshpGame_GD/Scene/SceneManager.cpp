#include "SceneManager.h"
#include <cassert>

SceneManager::SceneManager():
	m_isPrac(false),
	m_kind(kSceneTitle),
	m_nextScene (NextSceneState::nextGameMain),
	m_lastScene()
{
}
SceneManager::~SceneManager()
{

}

// 初期化
void SceneManager::Init(int font24, int font48)
{	
	// 各シーンの初期化
	m_kind = kSceneTitle;
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.SetManager(this);
		m_title.SetStageSelect(&m_stageSelect);
		m_title.Init();	// シーンタイトルの初期化
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.SetManager(this);
		m_stageSelect.SetMain(&m_main);
		m_stageSelect.SetTitle(&m_title);
		m_stageSelect.Init();	// シーンの初期化
		break;
	case SceneManager::kSceneHowTo:
		m_howTo.SetClear(&m_clear);
		m_howTo.Init(font24, font48);	// シーンクリアの初期化
		break;
	case SceneManager::kSceneRanking:
		m_ranking.Init(font24);	// シーンクリアの初期化
		break;
	case SceneManager::kSceneMain:
		m_main.SetManager(this);
		m_main.SetClear(&m_clear);
		m_main.SetRanking(&m_ranking);
		m_main.Init();	// シーンメインの初期化
		break;
	case SceneManager::kSceneClear:
		m_clear.Init(font24);	// シーンクリアの初期化
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 削除
void SceneManager::End()
{
	// 各シーンのデータ削除
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.End();	// シーンタイトルのデータ削除
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.End();	// シーンクリアのデータ削除
		break;
	case SceneManager::kSceneHowTo:
		m_howTo.End();	// シーンクリアの初期化
		break;
	case SceneManager::kSceneRanking:
		m_ranking.End();	// シーンクリアの初期化
		break;
	case SceneManager::kSceneMain:
		m_main.End();	// シーンメインのデータ削除
		break;
	case SceneManager::kSceneClear:
		m_main.End();	// シーンメインのデータ削除
		m_clear.End();	// シーンクリアのデータ削除
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 更新
void SceneManager::Update(const InputState& input, int font24, int font48, bool &isGameEnd)
{
	// 現在のシーンの更新処理を実行する
	bool isEnd = false;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Update(input, isGameEnd, m_nextScene, m_isPrac);	// シーンタイトルの更新
		isEnd = m_title.IsEnd();
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.Update(input, isGameEnd, m_nextScene, m_isPrac);	// シーンクリアの更新
		isEnd = m_stageSelect.IsEnd();
		break;
	case SceneManager::kSceneHowTo:
		m_howTo.Update(input, m_nextScene);
		isEnd = m_howTo.IsEnd();
		break;
	case SceneManager::kSceneRanking:
		m_ranking.Update(input, isGameEnd, m_nextScene);	// シーンクリアの初期化
		isEnd = m_ranking.IsEnd();
		break;
	case SceneManager::kSceneMain:
		m_main.Update(input, m_nextScene);	// シーンメインの更新
		isEnd = m_main.IsEnd();
		break;
	case SceneManager::kSceneClear:
		m_clear.Update(input, m_nextScene, m_isPrac);	// シーンクリアの更新
		isEnd = m_clear.IsEnd();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}

	// isEnd が true のとき、各シーンの初期化とデータ削除を行う
	if (isEnd)
	{
		m_lastScene = m_kind;

		switch (m_nextScene)
		{
		case NextSceneState::nextTitle:	// シーンがゲームクリアの場合、ゲーム終了
			End();	// シーンクリアのデータ削除
			m_title.SetManager(this);
			m_title.SetStageSelect(&m_stageSelect);
			m_title.Init();	// シーンタイトルの初期化
			m_kind = kSceneTitle;
			break;
		case NextSceneState::nextStageSelect:
			End();	// シーンタイトルのデータ削除
			m_stageSelect.SetMain(&m_main);
			m_stageSelect.SetManager(this);
			m_stageSelect.SetTitle(&m_title);
			m_stageSelect.Init();	// シーンメインの初期化
			m_kind = kSceneStageSelect;
			break;
		case NextSceneState::nextHowTo:
			End();
			m_howTo.SetClear(&m_clear);
			m_howTo.Init(font24, font48);	// シーンクリアの初期化
			m_kind = kSceneHowTo;
			break;
		case NextSceneState::nextRanking:	// シーンがゲームクリアの場合、ゲーム終了
			End();	// シーンクリアのデータ削除
			m_ranking.SetMain(&m_main);
			m_ranking.Init(font24);	// シーンタイトルの初期化
			m_kind = kSceneRanking;
			break;
		case NextSceneState::nextGameMain:
			End();	// シーンタイトルのデータ削除
			m_main.SetClear(&m_clear);
			m_main.SetRanking(&m_ranking);
			m_main.SetPracticeMode(m_isPrac);
			m_main.Init();	// シーンメインの初期化
			m_kind = kSceneMain;
			break;
		case NextSceneState::nextClear:
			m_clear.Init(font24);	// シーンクリアの初期化
			m_kind = kSceneClear;
			break;
		default:
			assert(false);
			break;
		}
	}
}

// 描画
void SceneManager::Draw()
{
	// 現在のシーンの描画処理を行う
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Draw();	// シーンタイトルの描画
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.Draw();	// シーンクリアの描画
		break;
	case SceneManager::kSceneHowTo:
		m_howTo.Draw();
		break;
	case SceneManager::kSceneRanking:
		m_ranking.Draw();	// シーンタイトルの描画
		break;
	case SceneManager::kSceneMain:
		m_main.Draw();	// シーンメインの描画
		break;
	case SceneManager::kSceneClear:
		m_main.Draw();	// シーンメインの描画
		m_clear.Draw();	// シーンクリアの描画
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}
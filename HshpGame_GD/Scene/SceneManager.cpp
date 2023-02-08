#include "SceneManager.h"
#include <cassert>

SceneManager::SceneManager():
	m_isMusicEnd(false),
	m_isPrac(false),
	m_kind(kSceneTitle),
	m_nextScene (NextSceneState::nextGameMain)
{
}
SceneManager::~SceneManager()
{

}

// 初期化
void SceneManager::Init(SceneKind kind)
{	
	// 各シーンの初期化
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Init();	// シーンタイトルの初期化
		break;
	case SceneManager::kSceneMain:
		m_main.SetManager(this);
		m_main.Init();	// シーンメインの初期化
		break;
	case SceneManager::kSceneClear:
		m_clear.Init();	// シーンクリアの初期化
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
	case SceneManager::kSceneMain:
		m_main.End();	// シーンメインのデータ削除
		break;
	case SceneManager::kSceneClear:
		m_clear.end();	// シーンクリアのデータ削除
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 更新
void SceneManager::update(const InputState& input, bool &isGameEnd)
{
	// 現在のシーンの更新処理を実行する
	bool isEnd = false;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Update(input, isGameEnd, m_nextScene, m_isPrac);	// シーンタイトルの更新
		isEnd = m_title.IsEnd();
		break;
	case SceneManager::kSceneMain:
		m_main.Update(input, m_nextScene);	// シーンメインの更新
		isEnd = m_main.IsEnd();
		break;
	case SceneManager::kSceneClear:
		m_clear.Update(m_nextScene);	// シーンクリアの更新
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
		//switch (m_kind)
		//{
		//case SceneManager::kSceneTitle:
		//	m_title.end();	// シーンタイトルのデータ削除
		//	m_main.Init();	// シーンメインの初期化
		//	m_kind = kSceneMain;
		//	break;
		//case SceneManager::kSceneMain:
		//	// m_isGameClear が true の場合、ゲームクリアのシーンを初期化し選択
		//	if (m_main.IsGameClear())
		//	{
		//		m_isMusicEnd = true;
		//		m_main.End();	// シーンメインのデータ削除
		//		m_clear.init();	// シーンクリアの初期化
		//		m_kind = kSceneClear;
		//		break;
		//	}
		//	else // それ以外の場合、タイトルのシーンを初期化し選択
		//	{
		//		m_main.End();	// シーンメインのデータ削除
		//		m_title.init();	// シーンタイトルの初期化
		//		m_kind = kSceneTitle;
		//		break;
		//	}
		//case SceneManager::kSceneClear:	// シーンがゲームクリアの場合、ゲーム終了
		//	m_isMusicEnd = false;
		//	m_clear.end();	// シーンクリアのデータ削除
		//	m_title.init();	// シーンタイトルの初期化
		//	m_kind = kSceneTitle;
		//	break;
		//case SceneManager::kSceneKindNum:
		//default:
		//	assert(false);
		//	break;
		//}

		switch (m_nextScene)
		{
		case NextSceneState::nextGameMain:
			End();	// シーンタイトルのデータ削除
			m_main.SetPracticeMode(m_isPrac);
			m_main.Init();	// シーンメインの初期化
			m_kind = kSceneMain;
			break;
		case NextSceneState::nextClear:
			m_isMusicEnd = true;
			End();	// シーンメインのデータ削除
			m_clear.Init();	// シーンクリアの初期化
			m_kind = kSceneClear;
			break;
		case NextSceneState::nextMenu:	// シーンがゲームクリアの場合、ゲーム終了
			End();	// シーンクリアのデータ削除
			m_title.Init();	// シーンタイトルの初期化
			m_kind = kSceneTitle;
			break;
		case NextSceneState::nextStageSelect:
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
	case SceneManager::kSceneMain:
		m_main.Draw();	// シーンメインの描画
		break;
	case SceneManager::kSceneClear:
		m_clear.Draw();	// シーンクリアの描画
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}
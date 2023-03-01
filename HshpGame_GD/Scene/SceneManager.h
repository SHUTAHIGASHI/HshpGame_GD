#pragma once

#include "game.h"
#include <memory>

class SceneTitle;
class SceneStageSelect;
class SceneHowTo;
class SceneRanking;
class SceneMain;
class SceneClear;

class SceneManager
{
public:
	// �V�[���̎�ޒ�`
	typedef enum SceneKind
	{
		kSceneTitle,
		kSceneHowTo,
		kSceneRanking,
		kSceneStageSelect,
		kSceneMain,
		kSceneClear,

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	// ������
	void Init(int font24, int font48);
	// �폜
	void End();

	// �X�V
	void Update(const InputState& input, int font24, int font48, bool &isGameEnd);
	// �`��
	void Draw();

	SceneKind GetLastScene() { return m_lastScene; }
	NextSceneState GetNextScene() { return m_nextScene; }

private:
	// ���K���[�h
	bool m_isPrac;
	
	SceneKind m_kind;
	SceneKind m_lastScene;
	NextSceneState m_nextScene;

	std::shared_ptr<SceneTitle> m_pTitle;
	std::shared_ptr<SceneStageSelect> m_pStageSelect;
	std::shared_ptr<SceneHowTo> m_pHowTo;
	std::shared_ptr<SceneRanking> m_pRanking;
	std::shared_ptr<SceneMain> m_pMain;
	std::shared_ptr<SceneClear> m_pClear;
};
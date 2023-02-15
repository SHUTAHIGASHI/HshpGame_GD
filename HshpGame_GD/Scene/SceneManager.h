#pragma once

#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneStageSelect.h"
#include "SceneRanking.h"

class SceneManager
{
public:
	// �V�[���̎�ޒ�`
	typedef enum SceneKind
	{
		kSceneTitle,
		kSceneHelp,
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
	void Init(SceneKind kind = kSceneTitle);
	// �폜
	void End();

	// �X�V
	void Update(const InputState& input, bool &isGameEnd);
	// �`��
	void Draw();

	SceneKind GetLastScene() { return m_lastScene; }

private:
	// ���K���[�h
	bool m_isPrac;
	
	SceneKind m_kind;
	SceneKind m_lastScene;
	NextSceneState m_nextScene;

	SceneTitle	m_title;
	SceneStageSelect m_stageSelect;
	SceneRanking m_ranking;
	SceneMain	m_main;
	SceneClear	m_clear;
};
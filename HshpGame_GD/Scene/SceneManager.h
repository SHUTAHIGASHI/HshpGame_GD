#pragma once

#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneStageSelect.h"

class SceneManager
{
public:
	// �V�[���̎�ޒ�`
	typedef enum SceneKind
	{
		kSceneTitle,
		kSceneHelp,
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
	
	SceneKind	m_kind;
	NextSceneState m_nextScene;
	SceneKind m_lastScene;

	SceneTitle	m_title;
	SceneStageSelect m_stageSelect;
	SceneMain	m_main;
	SceneClear	m_clear;
};
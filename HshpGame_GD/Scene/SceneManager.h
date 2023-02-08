#pragma once

#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"

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
	void update(const InputState& input, bool &isGameEnd);
	// �`��
	void Draw();

	// m_isMusicEnd ���擾
	bool IsGameMusicEnd() { return m_isMusicEnd; }

private:
	// �Q�[���I��
	bool m_isMusicEnd;

	// ���K���[�h
	bool m_isPrac;
	
	SceneKind	m_kind;
	NextSceneState m_nextScene;

	SceneTitle	m_title;
	SceneMain	m_main;
	SceneClear	m_clear;
};
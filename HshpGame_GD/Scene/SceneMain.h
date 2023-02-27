#pragma once
#include "game.h"
#include "Stage.h"
#include <memory>

class Player;
class Stage;
class SceneManager;
class SceneClear;
class SceneRanking;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void SetManager(SceneManager* manager) { m_pManager = manager; }
	void SetClear(SceneClear* clear) { m_pClear = clear; }
	void SetRanking(SceneRanking* rank) { m_pRanking = rank; }

	// ������
	void Init();

	void OnGameStart();

	void PlayGameSound();

	// �I������
	void End();

	// ���t���[���̏���
	void Update(const InputState& input, NextSceneState& nextScene);
	// ���t���[���̕`��
	void Draw();

	void DrawStartCount();

	// �X�e�[�W�N���A��
	void OnStageClear(NextSceneState& nextScene);

	// m_isEnd���擾
	virtual bool IsEnd() const { return m_isEnd; }

	// �`�������W���[�h�ɃZ�b�g
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }
	// �I�񂾃X�e�[�W���Z�b�g
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

	int GetAttempt() const { return m_countAttempt; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

private:
	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hDeathEffect;
	// �I�u�W�F�N�g�̃O���t�B�b�N�n���h��
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	int m_hJumpPad;
	// �w�i�̃O���t�B�b�N
	int m_hBg;

	// ���ʉ�
	int m_hDeathSound;
	// ���y�p
	int m_hPracBgm;
	int m_hChallengeBgm;
	int m_hPlayBgm;

	int m_fadeCount;

	// �X�N���[���p
	int m_scroll;
	// �Q�[���̐�������
	int m_startDelay;
	// �X�^�[�g�x�����̃e�L�X�g�T�C�Y
	int m_startTextSize;
	// �Q�[���I�[�o�[���̒x������
	int m_gameOverDelay;
	// �����
	int m_countAttempt;

	// �Q�[�����[�h
	bool m_isPracticeMode;

	// �V�[���I��
	bool m_isEnd;

	// �I�΂ꂽ�X�e�[�W
	StageState m_selectedStage;

	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// �X�e�[�W
	std::shared_ptr<Stage> m_pStage;

	SceneManager* m_pManager;
	SceneClear* m_pClear;
	SceneRanking* m_pRanking;
};
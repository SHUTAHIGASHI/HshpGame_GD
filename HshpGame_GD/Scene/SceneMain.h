#pragma once
#include "game.h"
#include "Stage.h"
#include <memory>
#include <string>

class Player;
class Stage;
class ScenePause;
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
	void Init(int fontS, int fontL);

	void OnGameStart();

	void PlayGameLoopBgm();

	// �I������
	void End();

	// ���t���[���̏���
	void Update(const InputState& input, NextSceneState& nextScene);
	
	// ���g���C�I�����̏���
	void OnRetry();
	// ���S���̏���
	void OnDead();

	// ���t���[���̕`��
	void Draw();
	// �Q�[�����̏��`��
	void DrawGameInfo();

	// ��������`��
	void DrawHowTo(int X, int Y);
	// �Q�[���X�^�[�g���̃J�E���g�_�E���`��
	void OnStartCount();

	// �X�e�[�W�N���A��
	void OnStageClear(NextSceneState& nextScene);

	// m_isEnd���擾
	virtual bool IsEnd() const { return m_isEnd; }

	// ���[�h�؂�ւ�
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }
	virtual void SetArcadeMode() { m_isArcadeMode = true; }
	virtual void SetTutorialMode() { m_isTutorial = true; }
	virtual void SetDoTutorialMode() { m_isDoTutorial = true; }

	// �I�񂾃X�e�[�W���Z�b�g
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

	// ���݂̃X�e�[�W���擾
	StageState GetStageState() const { return m_pStage->GetStageState(); }

	// ����񐔂��擾
	int GetAttempt() const { return m_countAttempt; }

	// BGM�n���h���擾
	int GetMusicHandle() const { return m_hPlayBgm; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// �ʏ�̍X�V����
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);
	// �X�^�[�g�J�E���g���̍X�V����
	void StartDelayUpdate(const InputState& input, NextSceneState& nextScene);
	// �V�[���ύX���̍X�V����
	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);
	void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);
private:
	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hDeathEffect;
	// �I�u�W�F�N�g�̃O���t�B�b�N�n���h��
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	int m_hJumpPad;
	int m_hPadImg;
	// �w�i�̃O���t�B�b�N
	int m_hBg;
	// �t�H���g�f�[�^
	int m_hFontL;
	int m_hFontS;
	// ���ʉ�
	int m_hDeathSound;
	int m_hCountDown;
	// ���y�p
	int m_hPlayBgm;

	// ���t���[���J�E���g
	int m_countFrame;

	// �t�F�[�h�����p�J�E���g
	int m_fadeCount;

	// �p�b�h�J�E���g
	int m_padCount;

	// �Q�[���̐�������
	int m_startDelay;
	// �X�^�[�g�x�����̃e�L�X�g�T�C�Y
	int m_startTextSize;
	// �X�^�[�g�x���̕����_��
	int m_textTimer;
	// �Q�[���I�[�o�[���̒x������
	int m_gameOverDelay;
	// �����
	int m_countAttempt;
	// ����񐔕`�掞��
	int m_attemptDrawTime;
	// ����񐔕`��̒l
	int m_attemptDrawNum;

	// �Q�[�����[�h
	bool m_isPracticeMode;
	bool m_isArcadeMode;
	bool m_isTutorial;
	bool m_isDoTutorial;

	// �|�[�Y�����ǂ���
	bool m_isPause;
	bool m_isPauseEnd;
	// �V�[���I��
	bool m_isEnd;

	// �J�E���g�_�E������x����
	bool m_isOnlyOnceSE;

	std::string m_tutorialText;

	// �I�΂ꂽ�X�e�[�W
	StageState m_selectedStage;

	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;
	// �X�e�[�W
	std::shared_ptr<Stage> m_pStage;

	// �|�[�Y���j���[�V�[��
	std::shared_ptr<ScenePause> m_pPause;

	SceneManager* m_pManager;
	SceneClear* m_pClear;
	SceneRanking* m_pRanking;
};
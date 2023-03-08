#pragma once
#include "game.h"
#include "Stage.h"
#include <memory>

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
	void Init();

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
	// �Q�[���X�^�[�g���̃J�E���g�_�E���`��
	void OnStartCount();

	// �X�e�[�W�N���A��
	void OnStageClear(NextSceneState& nextScene);

	// m_isEnd���擾
	virtual bool IsEnd() const { return m_isEnd; }

	// �`�������W���[�h�ɃZ�b�g
	virtual void SetPracticeMode(bool isPrac) { m_isPracticeMode = isPrac; }
	// �I�񂾃X�e�[�W���Z�b�g
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

	// ����񐔂��擾
	int GetAttempt() const { return m_countAttempt; }

	int GetMusicHandle() const { return m_hPlayBgm; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// �ʏ�̍X�V����
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	// �X�^�[�g�J�E���g���̍X�V����
	void StartDelayUpdate(const InputState& input, NextSceneState& nextScene);

	// �V�[���X�^�[�g���̍X�V����
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
	int m_hPlayBgm;

	// �t�F�[�h�����p�J�E���g
	int m_fadeCount;

	// �X�N���[���p
	int m_scroll;
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

	// �|�[�Y�����ǂ���
	bool m_isPause;
	// �V�[���I��
	bool m_isEnd;

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
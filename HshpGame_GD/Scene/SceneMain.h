#pragma once

#include "Player.h"
#include "Stage.h"
#include "ObjectBlock.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	void Init();

	void GameSetting();

	void PlayGameSound();

	// �I������
	void End();

	// ���t���[���̏���
	void Update(const InputState& input);
	// ���t���[���̕`��
	void Draw();

	// �X�e�[�W�N���A��
	void OnStageClear();

	// m_isGameClear���擾
	virtual bool IsGameClear() const { return m_isGameClear; }
	// m_isEnd���擾
	virtual bool IsEnd() const { return m_isEnd; }

private:
	// �Б��̓G�̍ő�o����
	static constexpr int kEnemyMax = 10;

private:
	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_playerHandle;
	int m_deathEffectHandle;
	// �I�u�W�F�N�g�̃O���t�B�b�N�n���h��
	int m_hObjectSpike;
	// �w�i�̃O���t�B�b�N
	int m_hBg;

	// ���y�p
	int m_hPracBgm;
	int m_hChallengeBgm;
	int m_hPlayBgm;

	// �X�N���[���p
	int m_scroll;
	// �Q�[���̐�������
	int m_startDelay;
	// �Q�[���I�[�o�[���̒x������
	int m_gameOverDelay;
	// �����
	int m_countAttempt;

	// �Q�[�����[�h
	bool m_isPracticeMode;

	// �Q�[���N���A
	bool m_isGameClear;
	// �V�[���I��
	bool m_isEnd;

	// �v���C���[
	Player m_Player;
	// �X�e�[�W
	Stage m_Stage;
};
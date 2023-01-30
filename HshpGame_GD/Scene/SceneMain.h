#pragma once

#include "playerCube.h"
#include "Stage.h"
#include "ObjectBlock.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	void Init();
	// �I������
	void End();

	// ���t���[���̏���
	void Update(const InputState& input);
	// ���t���[���̕`��
	void Draw();

	// m_isGameClear���擾
	virtual bool IsGameClear() const { return m_isGameClear; }
	// m_isEnd���擾
	virtual bool IsEnd() const { return m_isEnd; }

private:
	// �Б��̓G�̍ő�o����
	static constexpr int kEnemyMax = 10;

private:
	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_playerImg;
	int m_deathEffectImg;
	// �I�u�W�F�N�g�̃O���t�B�b�N�n���h��
	int m_hObjectSpike;

	// �Q�[���̐�������
	int m_gameTimeRemaining;
	// �Q�[���I�[�o�[���̒x������
	int m_gameOverDelay;

	// �����
	int m_countAttempt;

	// �Q�[���N���A
	bool m_isGameClear;

	// �V�[���I��
	bool m_isEnd;

	// �v���C���[
	PlayerCube m_Player;

	// �X�e�[�W
	Stage m_Stage;
};
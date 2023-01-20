#pragma once

#include "player.h"
#include "playerCube.h"
#include "Stage.h"
#include "ObjectBlock.h"

#include "Hp.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	void init();
	// �I������
	void end();

	// ���t���[���̏���
	void update(const InputState& input);
	// ���t���[���̕`��
	void draw();

	// m_isGameClear���擾
	virtual bool isGameClear() { return m_isGameClear; }
	// m_isEnd���擾
	virtual bool isEnd() { return m_isEnd; }

private:
	// �Б��̓G�̍ő�o����
	static constexpr int kEnemyMax = 10;

private:
	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic;

	// �Q�[���̐�������
	int m_gameTimeRemaining;
	// �Q�[���I�[�o�[���̒x������
	int m_GameOverDelay;
	// �G�̏o���x��
	int m_spawnDelay;

	// �Q�[���N���A
	bool m_isGameClear;

	// �V�[���I��
	bool m_isEnd;

	// �v���C���[
	Player m_Player;
	PlayerCube m_cPlayer;
	Stage m_Stage;

	Hp hp;
};
#pragma once

#include "ObjectBlock.h"
#include "game.h"
#include <memory>

class HowToPlayer;
class HowToStage;
class SceneClear;

class SceneHowTo
{
public:
	SceneHowTo();
	virtual ~SceneHowTo();

	void SetClear(SceneClear* clear) { m_pClear = clear; }

	// ������
	void Init(int font24, int font48);

	void OnGameStart();

	void PlayGameSound();

	// �I������
	void End();

	// ���t���[���̏���
	void Update(const InputState& input, NextSceneState& nextScene);
	// ���t���[���̕`��
	void Draw();

	void DrawHowTo();

	// m_isEnd���擾
	virtual bool IsEnd() const { return m_isEnd; }

private:
	using m_tUpdateFunc = void (SceneHowTo::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

private:
	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hPlayerWaveBurner;
	int m_hDeathEffect;
	// �I�u�W�F�N�g�̃O���t�B�b�N�n���h��
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	// �w�i�̃O���t�B�b�N
	int m_hBg;

	// �t�H���g�n���h��
	int m_hFontS;
	int m_hFontL;

	// ���ʉ�
	int m_hDeathSound;
	// ���y�p
	int m_hPracBgm;

	int m_fadeCount;

	int m_countFrame;
	// �Q�[���̐�������
	int m_startDelay;
	// �X�^�[�g�x�����̃e�L�X�g�T�C�Y
	int m_startTextSize;
	// �Q�[���I�[�o�[���̒x������
	int m_gameOverDelay;

	bool m_isPrac;
	// �V�[���I��
	bool m_isEnd;

	// �v���C���[
	std::shared_ptr<HowToPlayer> m_pHPlayer;
	
	// �X�e�[�W
	std::shared_ptr<HowToStage> m_pHStage;

	SceneClear* m_pClear;
};
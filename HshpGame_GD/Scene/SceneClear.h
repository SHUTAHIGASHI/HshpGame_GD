#pragma once
#include "SceneBase.h"
#include "game.h"
#include <string>
#include <memory>
#include <array>

class SceneMain;
class ParticleBase;

class SceneClear : public SceneBase
{
public:
	SceneClear():
		m_hSelectSound(-1),
		m_hFontS(-1),
		m_hFontL(-1),
		m_selectPos(0),
		m_selectNamePos(0),
		m_sceneChangeDelay(0),
		m_fadeCount(0),
		m_shadowScale(0),
		m_textFadeNum(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_isEnd(false),
		sinRate(0),
		auraFrame(0),
		m_pMain(nullptr)
	{
	}
	virtual ~SceneClear() {}

	// ���C���̃|�C���^�Z�b�g
	void SetMain(SceneMain* main) { m_pMain = main; }

	// ������
	void Init(int fontS, int fontL);
	
	// �I������
	void End();
	// �X�V
	void Update(const InputState& input, NextSceneState& nextScene);
	// �p�[�e�B�N���p
	void ParticleUpdate();
	// �w�肵���F�������_���Ɏ擾
	int GetRandColor();
	
	// �`��
	virtual void Draw();

	// �X�e�[�W�S�N����
	void OnAllClear();

	// ���̃X�e�[�W�֐i�ނ��ǂ���
	bool IsNextStage() const { return m_isNextStage; }

	// m_isEnd ���擾
	virtual bool IsEnd() { return m_isEnd; }

	void ResetIsNext() { m_isNextStage = false; }

private:
	// Update
	using m_tUpdateFunc = void (SceneClear::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// �ʏ�X�V����
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	// �X�e�[�W�S�N�����X�V����
	void AllClearUpdate(const InputState& input, NextSceneState& nextScene);

	// �V�[���I�����X�V����
	void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);

	// Draw
	using m_tDrawFunc = void (SceneClear::*) ();
	m_tDrawFunc m_drawFunc = nullptr;

	// �ʏ�̕`�揈��
	void NormalDraw();

	// �X�e�[�W�S�N�����̕`�揈��
	void AllClearDraw();
private:
	// ���f�[�^
	int m_hSelectSound;

	// �t�H���g�̃n���h��
	int m_hFontS;
	int m_hFontL;

	// ���j���[�I��
	int m_selectPos;
	int m_selectNamePos;
	
	// �^�C�g���\���܂ł̒x���p�ϐ�
	int m_sceneChangeDelay;
	
	// ��ʃt�F�[�h����
	int m_fadeCount;
	// �Q�[���N���A�e�L�X�g�̉e
	int m_shadowScale;
	int m_textFadeNum;

	// �e�L�X�g�̕����T�C�Y
	int m_textScale;
	int m_textScaleAcc;

	// ���̃X�e�[�W
	bool m_isNextStage;
	// �V�[���I��
	bool m_isEnd;

	// �p�[�e�B�N���p
	float sinRate;
	int auraFrame;
	std::array<std::shared_ptr<ParticleBase>, Game::kParticleNum> particle;

	SceneMain* m_pMain;
};
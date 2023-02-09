#include "SceneManager.h"
#include <cassert>

SceneManager::SceneManager():
	m_isMusicEnd(false),
	m_isPrac(false),
	m_kind(kSceneTitle),
	m_nextScene (NextSceneState::nextGameMain)
{
}
SceneManager::~SceneManager()
{

}

// ������
void SceneManager::Init(SceneKind kind)
{	
	// �e�V�[���̏�����
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Init();	// �V�[���^�C�g���̏�����
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.SetMain(&m_main);
		m_stageSelect.Init();	// �V�[���̏�����
		break;
	case SceneManager::kSceneMain:
		m_main.SetManager(this);
		m_main.Init();	// �V�[�����C���̏�����
		break;
	case SceneManager::kSceneClear:
		m_clear.Init();	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// �폜
void SceneManager::End()
{
	// �e�V�[���̃f�[�^�폜
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.End();	// �V�[���^�C�g���̃f�[�^�폜
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.end();	// �V�[���N���A�̃f�[�^�폜
		break;
	case SceneManager::kSceneMain:
		m_main.End();	// �V�[�����C���̃f�[�^�폜
		break;
	case SceneManager::kSceneClear:
		m_clear.end();	// �V�[���N���A�̃f�[�^�폜
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// �X�V
void SceneManager::update(const InputState& input, bool &isGameEnd)
{
	// ���݂̃V�[���̍X�V���������s����
	bool isEnd = false;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Update(input, isGameEnd, m_nextScene, m_isPrac);	// �V�[���^�C�g���̍X�V
		isEnd = m_title.IsEnd();
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.Update(input, isGameEnd, m_nextScene, m_isPrac);	// �V�[���N���A�̍X�V
		isEnd = m_stageSelect.IsEnd();
		break;
	case SceneManager::kSceneMain:
		m_main.Update(input, m_nextScene);	// �V�[�����C���̍X�V
		isEnd = m_main.IsEnd();
		break;
	case SceneManager::kSceneClear:
		m_clear.Update(m_nextScene);	// �V�[���N���A�̍X�V
		isEnd = m_clear.IsEnd();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}

	// isEnd �� true �̂Ƃ��A�e�V�[���̏������ƃf�[�^�폜���s��
	if (isEnd)
	{
		switch (m_nextScene)
		{
		case NextSceneState::nextMenu:	// �V�[�����Q�[���N���A�̏ꍇ�A�Q�[���I��
			End();	// �V�[���N���A�̃f�[�^�폜
			m_title.Init();	// �V�[���^�C�g���̏�����
			m_kind = kSceneTitle;
			break;
		case NextSceneState::nextStageSelect:
			End();	// �V�[���^�C�g���̃f�[�^�폜
			m_stageSelect.SetMain(&m_main);
			m_stageSelect.Init();	// �V�[�����C���̏�����
			m_kind = kSceneStageSelect;
			break;
		case NextSceneState::nextGameMain:
			End();	// �V�[���^�C�g���̃f�[�^�폜
			m_main.SetPracticeMode(m_isPrac);
			m_main.Init();	// �V�[�����C���̏�����
			m_kind = kSceneMain;
			break;
		case NextSceneState::nextClear:
			m_isMusicEnd = true;
			End();	// �V�[�����C���̃f�[�^�폜
			m_clear.Init();	// �V�[���N���A�̏�����
			m_kind = kSceneClear;
			break;
		default:
			assert(false);
			break;
		}
	}
}

// �`��
void SceneManager::Draw()
{
	// ���݂̃V�[���̕`�揈�����s��
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.Draw();	// �V�[���^�C�g���̕`��
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.Draw();	// �V�[���N���A�̕`��
		break;
	case SceneManager::kSceneMain:
		m_main.Draw();	// �V�[�����C���̕`��
		break;
	case SceneManager::kSceneClear:
		m_clear.Draw();	// �V�[���N���A�̕`��
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}
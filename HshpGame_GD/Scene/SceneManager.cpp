#include "SceneManager.h"
#include <cassert>

SceneManager::SceneManager():
	m_isPrac(false),
	m_kind(kSceneTitle),
	m_nextScene (NextSceneState::nextGameMain),
	m_lastScene()
{
}
SceneManager::~SceneManager()
{

}

// ������
void SceneManager::Init(int font24, int font48)
{	
	// �e�V�[���̏�����
	m_kind = kSceneTitle;
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_title.SetManager(this);
		m_title.SetStageSelect(&m_stageSelect);
		m_title.Init();	// �V�[���^�C�g���̏�����
		break;
	case SceneManager::kSceneStageSelect:
		m_stageSelect.SetManager(this);
		m_stageSelect.SetMain(&m_main);
		m_stageSelect.SetTitle(&m_title);
		m_stageSelect.Init();	// �V�[���̏�����
		break;
	case SceneManager::kSceneHowTo:
		m_howTo.SetClear(&m_clear);
		m_howTo.Init(font24, font48);	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneRanking:
		m_ranking.Init(font24);	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneMain:
		m_main.SetManager(this);
		m_main.SetClear(&m_clear);
		m_main.SetRanking(&m_ranking);
		m_main.Init();	// �V�[�����C���̏�����
		break;
	case SceneManager::kSceneClear:
		m_clear.Init(font24);	// �V�[���N���A�̏�����
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
		m_stageSelect.End();	// �V�[���N���A�̃f�[�^�폜
		break;
	case SceneManager::kSceneHowTo:
		m_howTo.End();	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneRanking:
		m_ranking.End();	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneMain:
		m_main.End();	// �V�[�����C���̃f�[�^�폜
		break;
	case SceneManager::kSceneClear:
		m_main.End();	// �V�[�����C���̃f�[�^�폜
		m_clear.End();	// �V�[���N���A�̃f�[�^�폜
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// �X�V
void SceneManager::Update(const InputState& input, int font24, int font48, bool &isGameEnd)
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
	case SceneManager::kSceneHowTo:
		m_howTo.Update(input, m_nextScene);
		isEnd = m_howTo.IsEnd();
		break;
	case SceneManager::kSceneRanking:
		m_ranking.Update(input, isGameEnd, m_nextScene);	// �V�[���N���A�̏�����
		isEnd = m_ranking.IsEnd();
		break;
	case SceneManager::kSceneMain:
		m_main.Update(input, m_nextScene);	// �V�[�����C���̍X�V
		isEnd = m_main.IsEnd();
		break;
	case SceneManager::kSceneClear:
		m_clear.Update(input, m_nextScene, m_isPrac);	// �V�[���N���A�̍X�V
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
		m_lastScene = m_kind;

		switch (m_nextScene)
		{
		case NextSceneState::nextTitle:	// �V�[�����Q�[���N���A�̏ꍇ�A�Q�[���I��
			End();	// �V�[���N���A�̃f�[�^�폜
			m_title.SetManager(this);
			m_title.SetStageSelect(&m_stageSelect);
			m_title.Init();	// �V�[���^�C�g���̏�����
			m_kind = kSceneTitle;
			break;
		case NextSceneState::nextStageSelect:
			End();	// �V�[���^�C�g���̃f�[�^�폜
			m_stageSelect.SetMain(&m_main);
			m_stageSelect.SetManager(this);
			m_stageSelect.SetTitle(&m_title);
			m_stageSelect.Init();	// �V�[�����C���̏�����
			m_kind = kSceneStageSelect;
			break;
		case NextSceneState::nextHowTo:
			End();
			m_howTo.SetClear(&m_clear);
			m_howTo.Init(font24, font48);	// �V�[���N���A�̏�����
			m_kind = kSceneHowTo;
			break;
		case NextSceneState::nextRanking:	// �V�[�����Q�[���N���A�̏ꍇ�A�Q�[���I��
			End();	// �V�[���N���A�̃f�[�^�폜
			m_ranking.SetMain(&m_main);
			m_ranking.Init(font24);	// �V�[���^�C�g���̏�����
			m_kind = kSceneRanking;
			break;
		case NextSceneState::nextGameMain:
			End();	// �V�[���^�C�g���̃f�[�^�폜
			m_main.SetClear(&m_clear);
			m_main.SetRanking(&m_ranking);
			m_main.SetPracticeMode(m_isPrac);
			m_main.Init();	// �V�[�����C���̏�����
			m_kind = kSceneMain;
			break;
		case NextSceneState::nextClear:
			m_clear.Init(font24);	// �V�[���N���A�̏�����
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
	case SceneManager::kSceneHowTo:
		m_howTo.Draw();
		break;
	case SceneManager::kSceneRanking:
		m_ranking.Draw();	// �V�[���^�C�g���̕`��
		break;
	case SceneManager::kSceneMain:
		m_main.Draw();	// �V�[�����C���̕`��
		break;
	case SceneManager::kSceneClear:
		m_main.Draw();	// �V�[�����C���̕`��
		m_clear.Draw();	// �V�[���N���A�̕`��
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}
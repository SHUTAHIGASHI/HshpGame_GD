#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneDemo.h"
#include "SceneStageSelect.h"
#include "SceneHowTo.h"
#include "SceneRanking.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include <cassert>

SceneManager::SceneManager():
	m_kind(kSceneTitle),
	m_nextScene (NextSceneState::nextGameMain),
	m_lastScene(),
	m_pTitle(std::make_shared<SceneTitle>()),
	m_pDemo(std::make_shared<SceneDemo>()),
	m_pStageSelect(std::make_shared<SceneStageSelect>()),
	m_pRanking(std::make_shared<SceneRanking>()),
	m_pMain(std::make_shared<SceneMain>()),
	m_pClear(std::make_shared<SceneClear>())
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
		m_pTitle->SetMain(m_pMain.get());
		m_pTitle->SetManager(this);
		m_pTitle->SetStageSelect(m_pStageSelect.get());
		m_pTitle->Init(font24, font48);	// �V�[���^�C�g���̏�����
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->Init();	// �V�[���^�C�g���̏�����
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->SetManager(this);
		m_pStageSelect->SetMain(m_pMain.get());
		m_pStageSelect->SetTitle(m_pTitle.get());
		m_pStageSelect->Init(font24, font48);	// �V�[���̏�����
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->Init(font24);	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneMain:
		m_pMain->SetManager(this);
		m_pMain->SetClear(m_pClear.get());
		m_pMain->SetRanking(m_pRanking.get());
		m_pMain->Init(font24, font48);	// �V�[�����C���̏�����
		break;
	case SceneManager::kSceneClear:
		m_pClear->SetMain(m_pMain.get());
		m_pClear->Init(font24);	// �V�[���N���A�̏�����
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
		m_pTitle->End();	// �V�[���^�C�g���̃f�[�^�폜
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->End();	// �V�[���^�C�g���̏�����
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->End();	// �V�[���N���A�̃f�[�^�폜
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->End();	// �V�[���N���A�̏�����
		break;
	case SceneManager::kSceneMain:
		m_pMain->End();	// �V�[�����C���̃f�[�^�폜
		break;
	case SceneManager::kSceneClear:
		m_pMain->End();	// �V�[�����C���̃f�[�^�폜
		m_pClear->End();	// �V�[���N���A�̃f�[�^�폜
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
		m_pTitle->Update(input, isGameEnd, m_nextScene);	// �V�[���^�C�g���̍X�V
		isEnd = m_pTitle->IsEnd();
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->Update(input, m_nextScene);	// �V�[���f���̏�����
		isEnd = m_pDemo->IsEnd();
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->Update(input, isGameEnd, m_nextScene);	// �V�[���N���A�̍X�V
		isEnd = m_pStageSelect->IsEnd();
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->Update(input, isGameEnd, m_nextScene);	// �V�[���N���A�̏�����
		isEnd = m_pRanking->IsEnd();
		break;
	case SceneManager::kSceneMain:
		m_pMain->Update(input, m_nextScene);	// �V�[�����C���̍X�V
		isEnd = m_pMain->IsEnd();
		break;
	case SceneManager::kSceneClear:
		m_pClear->Update(input, m_nextScene);	// �V�[���N���A�̍X�V
		isEnd = m_pClear->IsEnd();
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
			End();	// �V�[���̃f�[�^�폜
			m_pTitle->SetMain(m_pMain.get());
			m_pTitle->SetManager(this);
			m_pTitle->SetStageSelect(m_pStageSelect.get());
			m_pTitle->Init(font24, font48);	// �V�[���^�C�g���̏�����
			m_kind = kSceneTitle;
			break;
		case NextSceneState::nextDemo:	// �V�[�����Q�[���N���A�̏ꍇ�A�Q�[���I��
			End();	// �V�[���̃f�[�^�폜
			m_pDemo->Init();	// �V�[���^�C�g���̏�����
			m_kind = kSceneDemo;
			break;
		case NextSceneState::nextStageSelect:
			End();	// �V�[���̃f�[�^�폜
			m_pStageSelect->SetMain(m_pMain.get());
			m_pStageSelect->SetManager(this);
			m_pStageSelect->SetTitle(m_pTitle.get());
			m_pStageSelect->Init(font24, font48);	// �V�[�����C���̏�����
			m_kind = kSceneStageSelect;
			break;
		case NextSceneState::nextRanking:	// �V�[�����Q�[���N���A�̏ꍇ�A�Q�[���I��
			End();	// �V�[���̃f�[�^�폜
			m_pRanking->SetMain(m_pMain.get());
			m_pRanking->Init(font24);	// �V�[���^�C�g���̏�����
			m_kind = kSceneRanking;
			break;
		case NextSceneState::nextGameMain:
			End();	// �V�[���̃f�[�^�폜
			m_pMain->SetClear(m_pClear.get());
			m_pMain->SetRanking(m_pRanking.get());
			m_pMain->Init(font24, font48);	// �V�[�����C���̏�����
			m_kind = kSceneMain;
			break;
		case NextSceneState::nextClear:
			m_pClear->SetMain(m_pMain.get());
			m_pClear->Init(font24);	// �V�[���N���A�̏�����
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
		m_pTitle->Draw();	// �V�[���^�C�g���̕`��
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->Draw();	// �V�[���^�C�g���̕`��
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->Draw();	// �V�[���N���A�̕`��
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->Draw();	// �V�[���^�C�g���̕`��
		break;
	case SceneManager::kSceneMain:
		m_pMain->Draw();	// �V�[�����C���̕`��
		break;
	case SceneManager::kSceneClear:
		m_pMain->Draw();	// �V�[�����C���̕`��
		m_pClear->Draw();	// �V�[���N���A�̕`��
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}
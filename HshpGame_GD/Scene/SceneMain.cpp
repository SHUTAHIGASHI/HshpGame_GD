#include "SceneMain.h"
#include "Player.h"
#include "Stage.h"
#include "game.h"
#include "SceneClear.h"
#include "SceneRanking.h"
#include <cassert>
#include <memory>

namespace
{
	// �X�^�[�g���̒x������
	constexpr int kStartDelay = 300;
	// �X�^�[�g�J�E���g�_�E���̕����T�C�Y
	constexpr int kStartTextSizeMax = 100;
	// ���S���̒x��
	constexpr int kGameOverDelay = 30;
}

SceneMain::SceneMain() :
	m_pPlayer(std::make_shared<Player>()),
	m_pStage(std::make_shared<Stage>()),
	m_updateFunc(&SceneMain::SceneStartUpdate),
	m_hPlayer(-1),
	m_hDeathEffect(-1),
	m_hObjectSpike(-1),
	m_hPortal(-1),
	m_hBlock(-1),
	m_hJumpPad(-1),
	m_hBg(-1), 
	m_hDeathSound(-1),
	m_hPracBgm(-1),
	m_hChallengeBgm(-1),
	m_hPlayBgm(-1),
	m_fadeCount(0),
	m_scroll(0),
	m_startDelay(0), 
	m_startTextSize(0),
	m_gameOverDelay(0),
	m_countAttempt(0),
	m_isPracticeMode(false),
	m_isEnd(false),
	m_selectedStage(StageState::firstStage),
	m_pManager(nullptr),
	m_pClear(nullptr),
	m_pRanking(nullptr)
{
}

SceneMain::~SceneMain()
{
}

// ������
void SceneMain::Init()
{
	// �V�[���I���ϐ���������
	m_isEnd = false;	// �Q�[���I���t���O
	m_fadeCount = 255;	// �t�F�[�h�����̐��l
	m_updateFunc = &SceneMain::SceneStartUpdate;	// �t�F�[�h���������s����

	// �A�h���X�̐ݒ�
	m_pPlayer->SetStage(m_pStage.get());
	m_pStage->SetPlayer(m_pPlayer.get());

	// �摜�ǂݍ���
	m_hPlayer = LoadGraph(Game::kPlayerImg);	// �v���C���[�摜
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);	// ���S�G�t�F�N�g
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);	// �X�p�C�N�摜
	m_hPortal = LoadGraph("imagedata/OrangePortal.png");	// �S�[���|�[�^��
	m_hBlock = LoadGraph("imagedata/Tileset.png");	// �u���b�N
	m_hJumpPad = LoadGraph("imagedata/JumpPad.png");	// �W�����v�p�b�h
	m_hBg = LoadGraph("imagedata/Bg.png");	// �w�i�摜

	// ���f�[�^�̓ǂݍ���
	m_hDeathSound = LoadSoundMem("soundData/deathSound.mp3");	// ���S���̉�
	m_hPracBgm = LoadSoundMem("soundData/StayInsideMe.mp3");	// ���K���[�h��BGM
	m_hChallengeBgm = LoadSoundMem("soundData/ElectromanAdventuresV2.mp3");	// �`�������W���[�h��BGM

	// BGM�̃Z�b�g
	// ���K���[�h�̏ꍇ�A���K�pBGM���Z�b�g
	if (m_isPracticeMode) m_hPlayBgm = m_hPracBgm;
	// �`�������W���[�h�̏ꍇ�A�`�������W���[�h�pBGM���Z�b�g
	else m_hPlayBgm = m_hChallengeBgm;

	// �X�e�[�W�I��
	// �`�������W���[�h�̏ꍇ�A�X�e�[�W�P���Z�b�g
	if (!m_isPracticeMode) m_pStage->SetFirstStage();
	// �X�e�[�W���I�΂ꂽ�ꍇ�A���̃X�e�[�W�ɃZ�b�g
	else if (m_selectedStage != StageState::Empty) m_pStage->SetSelectedStage(m_selectedStage);
	// �N���A��� "���̃X�e�[�W" ���I�΂ꂽ�ꍇ�A���X�e�[�W���Z�b�g
	else if (m_pClear->IsNextStage()) m_pStage->SetNextStageState();
	else assert(0);

	// �X�^�[�g�x���̏�����
	m_startDelay = 0;// kStartDelay;
	// �X�^�[�g�J�E���g�_�E���̏�����
	m_startTextSize = kStartTextSizeMax;

	// ����񐔂̃J�E���g������
	m_countAttempt = 1;

	// �Q�[���X�^�[�g(�ăX�^�[�g)���̏���������
	OnGameStart();
}

// �Q�[���X�^�[�g(�ăX�^�[�g)���̏���������
void SceneMain::OnGameStart()
{	
	// �Q�[���I�[�o�[���̒x��������
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_pPlayer->Init(m_hPlayer, m_hDeathEffect, m_hDeathSound);
	// �X�e�[�W������
	m_pStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock, m_hJumpPad);
}

// �Q�[������BGM�Đ�
void SceneMain::PlayGameSound()
{
	// BGM������Ă��Ȃ��ꍇ�A�Ȃ��Đ�
	if(!CheckSoundMem(m_hPlayBgm)) PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK);
}

// �I������
void SceneMain::End()
{
	// �I�΂ꂽ�X�e�[�W����ɃZ�b�g
	m_selectedStage = StageState::Empty;

	// �X�e�[�W�̏I������
	m_pStage->End();

	// �T�E���h�̒�~
	StopSoundMem(m_hPlayBgm);

	// �摜�f�[�^�̍폜
	DeleteGraph(m_hPlayer);	// �v���C���[�摜
	DeleteGraph(m_hDeathEffect);	// ���S�G�t�F�N�g
	DeleteGraph(m_hObjectSpike);	// �X�p�C�N�摜
	DeleteGraph(m_hPortal);	// �S�[���|�[�^���摜
	DeleteGraph(m_hBlock);	// �u���b�N
	DeleteGraph(m_hBg);	// �w�i�摜

	// ���f�[�^�̍폜
	DeleteSoundMem(m_hDeathSound);	// ���S�T�E���h
	DeleteSoundMem(m_hPracBgm);	// ���K�pBGM
	DeleteSoundMem(m_hChallengeBgm);	// �`�������W���[�h�pBGM
	DeleteSoundMem(m_hPlayBgm);	// ���ݍĐ�����BGM
}

// ���t���[���̏���
void SceneMain::Update(const InputState& input, NextSceneState& nextScene)
{		
	(this->*m_updateFunc)(input, nextScene);
}

// ���t���[���̕`��
void SceneMain::Draw()
{
	// �X�e�[�W�̕`��
	m_pStage->Draw();

	// �Q�[���N���A���Ă���ꍇ�A�����I��
	if (m_pPlayer->IsStageClear()) return;

	// �v���C���[�̕`��
	m_pPlayer->Draw();
	
	// ����񐔂̕`��
	DrawFormatString(10, 60, 0xffffff, "Attempt : %d", m_countAttempt);
	// ���݂̃��[�h�̕`��
	if(m_isPracticeMode) DrawString(10, 100, "pracmode", 0xff0000);

	// �t�F�[�h�����p�̏���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �X�^�[�g���̃J�E���g�_�E���`��
	if (m_startDelay > 0)
	{
		DrawStartCount();
	}
}

// �X�^�[�g���̃J�E���g�_�E���`��
void SceneMain::DrawStartCount()
{
	// �����̃T�C�Y����
	// �]�肪 0 �ɂȂ����ꍇ�A�ݒ肵���t�H���g�T�C�Y�ɖ߂�
	if (m_startDelay % 60 == 0) m_startTextSize = kStartTextSizeMax;
	// ���t���[���t�H���g�T�C�Y������������
	m_startTextSize--;
	// �t�H���g�T�C�Y�� 60 ��菬�������Ȃ�
	if (m_startTextSize < 60) m_startTextSize = 60;

	// �J�E���g�_�E���`��
	if (m_startDelay / 60 == 5)
	{
		// �T�b�̏ꍇ�͉����`�悵�Ȃ�
	}
	else if (m_startDelay / 60 == 0)
	{
		// �O�b�̏ꍇ�� "GO!" �̕�����`��
		SetFontSize(m_startTextSize);
		// ���̔�����
		DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2) + 2, Game::kScreenHeightHalf + 5, "GO!", 0xe9e9e9);
		// �ԕ���
		DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2), Game::kScreenHeightHalf, "GO!", 0xff2222);
	}
	else
	{
		// �S�`�P�b�̊Ԃ͂��̐�����`��
		SetFontSize(m_startTextSize);
		// ���̔�����
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2) + 2, Game::kScreenHeightHalf + 5, 0xe9e9e9, "%d", m_startDelay / 60);
		// �ԕ���
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2), Game::kScreenHeightHalf, 0xff2222, "%d", m_startDelay / 60);
	}
	// �t�H���g�T�C�Y��W���ɖ߂�
	SetFontSize(20);
}

// �X�e�[�W�N���A���̏���
void SceneMain::OnStageClear(NextSceneState& nextScene)
{
	// �X�e�[�W�N���A�̃t���O�� true ���ǂ���
	if (m_pPlayer->IsStageClear())
	{
		// �X�e�[�W�P�O or ���K���[�h �̏ꍇ�̏���
		if (m_pStage->GetStageState() == StageState::tenthStage || m_isPracticeMode)
		{
			// �`�������W���[�h�̏ꍇ
			if (!m_isPracticeMode)
			{
				// �����L���O�f�[�^�ǂݍ���
				m_pRanking->LoadRankingData();
				// �����L���O�f�[�^�̍X�V
				m_pRanking->SetRanking(m_countAttempt, m_pStage->GetStageState());
			}

			// ����񐔂�������
			m_countAttempt = 1;
			// ���̃V�[����ݒ�
			nextScene = NextSceneState::nextClear;
			// �V�[���I���t���O
			m_isEnd = true;
		}
		else
		{
			// ���̃X�e�[�W��Ԃ��Z�b�g
			m_pStage->SetNextStageState();
			// �Q�[���X�^�[�g���̏�����
			OnGameStart();
		}
	}
}

// �ʏ펞�̍X�V����
void SceneMain::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	// escape�L�[�������ꂽ�ꍇ
	if (input.IsTriggered(InputType::escape))
	{
		// ���K���[�h�̏ꍇ�A�X�e�[�W�Z���N�g��
		if (m_isPracticeMode) nextScene = NextSceneState::nextStageSelect;
		// ����ȊO�̏ꍇ�A�^�C�g�����j���[��
		else nextScene = NextSceneState::nextTitle;
		// �V�[���I���t���O�� true
		m_isEnd = true;
	}

	// R�L�[�������ꂽ�ꍇ
	if (input.IsTriggered(InputType::retry))
	{
		// �`�������W���[�h�̏ꍇ�A�Ȃ��~
		if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

		// �`�������W���[�h�̏ꍇ�A�X�e�[�W�P���Z�b�g
		if (!m_isPracticeMode) m_pStage->SetFirstStage();
		// �Q�[����ԏ�����
		OnGameStart();
		// ����񐔂𑝂₷
		m_countAttempt++;
		return;
	}

	// �X�^�[�g�x���𖈃t���[�����炷
	m_startDelay--;
	// �X�^�[�g�x���� 1 �ȏ�̏ꍇ�����I��
	if (m_startDelay > 0) return;
	// �X�^�[�g�x���� 0 �ȉ��ɂȂ����炻��ȏ㌸��Ȃ�
	else
	{
		m_startDelay = 0;
		m_fadeCount = 0;
	}

	// �Q�[��BGM�Đ�
	PlayGameSound();

	// �X�e�[�W�̍X�V����
	m_pStage->Update();

	// �v���C���[�̍X�V����
	m_pPlayer->Update(input);

	// �X�e�[�W�N���A���̏���
	OnStageClear(nextScene);

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_pPlayer->IsDead())
	{
		// �Đ�����BGM���~�߂�
		if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

		// �Q�[���I�[�o�[�x�����O�ȉ��ɂȂ����ꍇ
		if (m_gameOverDelay < 0)
		{
			// �`�������W���[�h�̏ꍇ�A�X�e�[�W�P���Z�b�g
			if (!m_isPracticeMode) m_pStage->SetFirstStage();
			// �Q�[����ԏ�����
			OnGameStart();
			// ����񐔂𑝂₷
			m_countAttempt++;
			return;
		}

		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
		m_gameOverDelay--;
		return;
	}
}

// �V�[���J�n���̍X�V����
void SceneMain::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	// �t�F�[�h�̐��l���T�����炷
	m_fadeCount -= 5;
	
	// �t�F�[�h�J�E���g�� 150 �ȉ��ɂȂ����ꍇ
	if (m_fadeCount < 150)
	{
		// 150 �ɃZ�b�g
		m_fadeCount = 150;
		// �ʏ�̍X�V�������Z�b�g
		m_updateFunc = &SceneMain::NormalUpdate;
	}
}

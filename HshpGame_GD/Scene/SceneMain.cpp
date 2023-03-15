#include "SceneMain.h"
#include "game.h"
#include "Player.h"
#include "Stage.h"
#include "ScenePause.h"
#include "SceneClear.h"
#include "SceneRanking.h"
#include <cassert>
#include <memory>

namespace
{
	// �X�^�[�g���̒x������
	constexpr int kStartDelay = 240;
	// �X�^�[�g�J�E���g�_�E���̕����T�C�Y
	constexpr int kStartTextSizeMax = 100;
	// ���S���̒x��
	constexpr int kGameOverDelay = 30;
	// ����񐔕`�掞��
	constexpr int kAttemptDrawMax = 180;
}

SceneMain::SceneMain() :
	m_pPlayer(std::make_shared<Player>()),
	m_pStage(std::make_shared<Stage>()),
	m_pPause(std::make_shared<ScenePause>()),
	m_updateFunc(&SceneMain::SceneStartUpdate),
	m_hPlayer(-1),
	m_hDeathEffect(-1),
	m_hObjectSpike(-1),
	m_hPortal(-1),
	m_hBlock(-1),
	m_hJumpPad(-1),
	m_hPadImg(-1),
	m_hBg(-1),
	m_hFontL(-1),
	m_hFontS(-1),
	m_hDeathSound(-1),
	m_hCountDown(-1),
	m_hPlayBgm(-1),
	m_countFrame(0),
	m_fadeCount(0),
	m_padCount(0),
	m_startDelay(0),
	m_startTextSize(0),
	m_textTimer(0),
	m_gameOverDelay(0),
	m_countAttempt(0),
	m_attemptDrawTime(0),
	m_attemptDrawNum(0),
	m_isPracticeMode(false),
	m_isArcadeMode(false),
	m_isTutorial(false),
	m_isDoTutorial(false),
	m_isPause(false),
	m_isPauseEnd(false),
	m_isEnd(false),
	m_isOnlyOnceSE(false),
	m_tutorialText(),
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
void SceneMain::Init(int fontS, int fontL)
{
	// �V�[���I���ϐ���������
	m_isEnd = false;	// �Q�[���I���t���O
	m_isPause = false;
	m_isPauseEnd = false;
	m_isOnlyOnceSE = false;
	m_fadeCount = 255;	// �t�F�[�h�����̐��l
	m_updateFunc = &SceneMain::SceneStartUpdate;	// �t�F�[�h���������s����

	// �A�h���X�̐ݒ�
	m_pPlayer->SetStage(m_pStage.get());
	m_pStage->SetPlayer(m_pPlayer.get());
	m_pPause->SetMain(this);
	m_pPlayer->SetMain(this);
	m_pStage->SetMain(this);

	// �|�[�Y�V�[��������
	m_pPause->Init();

	// �摜�ǂݍ���
	m_hPlayer = LoadGraph(Game::kPlayerImg);	// �v���C���[�摜
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);	// ���S�G�t�F�N�g
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);	// �X�p�C�N�摜
	m_hPortal = LoadGraph(Game::kPortalImg);	// �S�[���|�[�^��
	m_hBlock = LoadGraph(Game::kBlockImg);	// �u���b�N
	m_hJumpPad = LoadGraph(Game::kJumpPadImg);	// �W�����v�p�b�h
	m_hPadImg = LoadGraph(Game::kPadImg); // �p�b�h�摜
	m_hBg = LoadGraph(Game::kBgImg);	// �w�i�摜

	// �t�H���g�f�[�^�̑��
	m_hFontL = fontL;
	m_hFontS = fontS;

	// ���f�[�^�̓ǂݍ���
	m_hDeathSound = LoadSoundMem(Game::kDeathSound);	// ���S���̉�
	m_hCountDown = LoadSoundMem("soundData/countDown.wav");

	// BGM�̃Z�b�g
	if (m_isArcadeMode) m_hPlayBgm = LoadSoundMem(Game::kArcadeBgm); // ���K���[�h�̏ꍇ�A���K�pBGM���Z�b�g
	else if (m_isPracticeMode) m_hPlayBgm = LoadSoundMem(Game::kPracBgm); // ���K���[�h�̏ꍇ�A���K�pBGM���Z�b�g
	else m_hPlayBgm = LoadSoundMem(Game::kChallengeBgm); // �`�������W���[�h�̏ꍇ�A�`�������W���[�h�pBGM���Z�b�g

	// �X�e�[�W�I�� //
	// �A�[�P�[�h���[�h�̏ꍇ
	if (m_isArcadeMode)
	{
		// �`���[�g���A�����s���ꍇ�̓`���[�g���A�����Z�b�g
		if (m_isDoTutorial) m_pStage->SetTutorialStage();
		// �s��Ȃ��ꍇ�̓X�e�[�W�P
		else m_pStage->SetFirstStage();
	}
	// �`�������W���[�h�̏ꍇ�A�X�e�[�W�P���Z�b�g
	else if (!m_isPracticeMode) m_pStage->SetFirstStage();
	// �X�e�[�W���I�΂ꂽ�ꍇ�A���̃X�e�[�W�ɃZ�b�g
	else if (m_selectedStage != StageState::Empty) m_pStage->SetSelectedStage(m_selectedStage);
	// �N���A��� "���̃X�e�[�W" ���I�΂ꂽ�ꍇ�A���X�e�[�W���Z�b�g
	else if (m_pClear->IsNextStage()) m_pStage->SetNextStageState();
	else assert(0);

	// �X�^�[�g�x���̏�����
	m_startDelay = kStartDelay;
	// �X�^�[�g�J�E���g�_�E���̏�����
	m_startTextSize = kStartTextSizeMax;

	// ����񐔂̃J�E���g������
	m_countAttempt = 1;

	m_padCount = 0;

	// �Q�[���X�^�[�g(�ăX�^�[�g)���̏���������
	OnGameStart();
}

// �Q�[���X�^�[�g(�ăX�^�[�g)���̏���������
void SceneMain::OnGameStart()
{
	// ����񐔃e�L�X�g�̕`�掞�ԃ��Z�b�g
	m_attemptDrawTime = kAttemptDrawMax;
	m_attemptDrawNum = 255;

	// �X�e�[�W���[�h
	m_isTutorial = false;

	// �Q�[���I�[�o�[���̒x��������
	m_gameOverDelay = kGameOverDelay;

	// �v���C���[������
	m_pPlayer->Init(m_hPlayer, m_hDeathEffect, m_hDeathSound);
	// �X�e�[�W������
	m_pStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock, m_hJumpPad);

	if (m_isTutorial)
	{
		if (m_pStage->GetStageState() == StageState::tutrialCube) m_tutorialText = "�{�^���ŃW�����v�I";
		else if (m_pStage->GetStageState() == StageState::tutrialJumpPad) m_tutorialText = "���Ƒ�W�����v";
		else if (m_pStage->GetStageState() == StageState::tutrialJumpRing) m_tutorialText = "�{�^���ő�W�����v";
		else if (m_pStage->GetStageState() == StageState::tutrialGravity) m_tutorialText = "�{�^���ŏd�͔��]�I";
		else if (m_pStage->GetStageState() == StageState::tutrialDash) m_tutorialText = "�{�^���ŋ󒆕��V�I";
		else if (m_pStage->GetStageState() == StageState::tutrialRev) m_tutorialText = "�{�^���ŕ����t�]�I";
		else m_tutorialText = "�ŃM�~�b�N���g�p�I";
	}
}

// �Q�[������BGM�Đ�
void SceneMain::PlayGameLoopBgm()
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
	// �|�[�Y�V�[���̏I������
	m_pPause->End();

	m_isPracticeMode = false;
	m_isArcadeMode = false;
	m_isTutorial = false;
	m_isDoTutorial = false;

	// �T�E���h�̒�~
	StopSoundMem(m_hPlayBgm, true);

	// �摜�f�[�^�̍폜
	DeleteGraph(m_hPlayer);	// �v���C���[�摜
	DeleteGraph(m_hDeathEffect);	// ���S�G�t�F�N�g
	DeleteGraph(m_hObjectSpike);	// �X�p�C�N�摜
	DeleteGraph(m_hPortal);	// �S�[���|�[�^���摜
	DeleteGraph(m_hBlock);	// �u���b�N
	DeleteGraph(m_hJumpPad);	// �W�����v�p�b�h
	DeleteGraph(m_hPadImg);	// �Q�[���p�b�h
	DeleteGraph(m_hBg);	// �w�i�摜

	// ���f�[�^�̍폜
	DeleteSoundMem(m_hDeathSound);	// ���S�T�E���h
	DeleteSoundMem(m_hCountDown);
	DeleteSoundMem(m_hPlayBgm);	// ���ݍĐ�����BGM
}

// ���t���[���̏���
void SceneMain::Update(const InputState& input, NextSceneState& nextScene)
{		
	if (m_isPause)
	{
		m_pPause->Update(input, nextScene, m_isPauseEnd);
		if (input.IsTriggered(InputType::pause))
		{
			m_isPause = false;
			PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK, false);
		}
		
		if (m_isPauseEnd)
		{
			m_isPause = false;
			m_updateFunc = &SceneMain::SceneEndUpdate;
		}

		return;
	}

	m_countFrame++;
	if (m_countFrame > 1000) m_countFrame = 0;

	if (m_isTutorial)
	{
		if (m_countFrame % 6 == 0)m_padCount++;
		if (m_padCount > 5) m_padCount = 1;
	}

	(this->*m_updateFunc)(input, nextScene);
}

// ���g���C�I�����̏���
void SceneMain::OnRetry()
{
	m_isPause = false;
	
	// �`�������W���[�h�̏ꍇ�A�Ȃ��~
	if (!m_isPracticeMode && !m_isArcadeMode) StopSoundMem(m_hPlayBgm);
	// �`�������W���[�h�̏ꍇ�A�X�e�[�W�P���Z�b�g
	if (!m_isPracticeMode && !m_isArcadeMode) m_pStage->SetFirstStage();
	// �Q�[����ԏ�����
	OnGameStart();
	// ����񐔂𑝂₷
	if(!m_isTutorial) m_countAttempt++;
	return;
}

void SceneMain::OnDead()
{
	// �Đ�����BGM���~�߂�
	if (!m_isPracticeMode && !m_isArcadeMode) StopSoundMem(m_hPlayBgm);

	// �Q�[���I�[�o�[�x�����O�ȉ��ɂȂ����ꍇ
	if (m_gameOverDelay < 0)
	{
		// �`�������W���[�h�̏ꍇ�A�X�e�[�W�P���Z�b�g
		if (!m_isPracticeMode && !m_isArcadeMode) m_pStage->SetFirstStage();
		// �Q�[����ԏ�����
		OnGameStart();
		// ����񐔂𑝂₷
		if (!m_isTutorial) m_countAttempt++;
		return;
	}

	// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
	m_gameOverDelay--;
}

// ���t���[���̕`��
void SceneMain::Draw()
{
	// �X�e�[�W�̕`��
	m_pStage->Draw();

	// �Q�[���N���A���Ă���ꍇ�A�����I��
	if (m_pPlayer->IsStageClear()) return;

	if (m_startDelay <= 0)
	{
		DrawGameInfo();
	}

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	if (m_isPause)
	{
		m_pPause->Draw();
		return;
	}
	
	// �t�F�[�h�����p�̏���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �X�^�[�g���̃J�E���g�_�E���`��
	if (m_startDelay > 0)
	{
		OnStartCount();
	}
}

void SceneMain::DrawGameInfo()
{
	if (m_isTutorial)
	{
		DrawHowTo(100, 100);
		return;
	}

	int drawX, drawY;
	if (m_attemptDrawTime > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_attemptDrawNum);
		drawX = static_cast<int>(m_pPlayer->GetPos().x - 100);
		drawY = static_cast<int>(m_pPlayer->GetPos().y - 50);
		if (drawX < 0) drawX = 0;

		SetFontSize(20);
		// ����񐔂̕`��
		DrawFormatString(drawX - m_pStage->GetScroll(), drawY, 0xe9e9e9, "Attempt : %d", m_countAttempt);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (m_isPracticeMode)
	{
		drawX = 10, drawY = 60;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(5, drawY, drawX + 190, drawY + 25, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetFontSize(20);
		// ���݂̃��[�h�̕`��
		DrawFormatString(drawX, drawY, 0xe9e9e9, "stage %02d", static_cast<int>(m_pStage->GetStageState()) + 1 - 6);
	}
}

void SceneMain::DrawHowTo(int X, int Y)
{
	int imgX = Game::kPadChipSize, imgY = Game::kPadChipSize;
	int imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;
	int drawPosX, drawPosY;

	drawPosX = X, drawPosY = Y - 30;
	DrawStringToHandle(drawPosX, drawPosY + 2, "�`�`���[�g���A���`", 0xe9e9e9, m_hFontS);
	DrawStringToHandle(drawPosX, drawPosY, "�`�`���[�g���A���`", 0xff0000, m_hFontS);
	
	drawPosX = X, drawPosY = Y;
	DrawStringToHandle(drawPosX, drawPosY, m_tutorialText.c_str(), 0xe9e9e9, m_hFontL);

	if (m_pStage->GetStageState() != StageState::tutrialJumpPad)
	{
		imgX = Game::kPadChipSize * m_padCount;
		imgY = Game::kPadChipSize * 12;
		DrawRectExtendGraph(drawPosX - 52, drawPosY,
			drawPosX - 2, drawPosY + 50,
			imgX, imgY, imgW, imgH, m_hPadImg, true);
	}
}

// �X�^�[�g���̃J�E���g�_�E���`��
void SceneMain::OnStartCount()
{
	std::string temp = "";

	// �����̃T�C�Y����
	// �]�肪 0 �ɂȂ����ꍇ�A�ݒ肵���t�H���g�T�C�Y�ɖ߂�
	if (m_startDelay % 60 == 0) m_startTextSize = kStartTextSizeMax;
	// ���t���[���t�H���g�T�C�Y������������
	m_startTextSize--;
	// �t�H���g�T�C�Y�� 60 ��菬�������Ȃ�
	if (m_startTextSize < 60) m_startTextSize = 60;

	// �J�E���g�_�E���`��
	if (m_startDelay / 60 == 4)
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
		// �R�`�P�b�̊Ԃ͂��̐�����`��
		SetFontSize(m_startTextSize);
		// ���̔�����
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2) + 2, Game::kScreenHeightHalf + 5, 0xe9e9e9, "%d", m_startDelay / 60);
		// �ԕ���
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2), Game::kScreenHeightHalf, 0xff2222, "%d", m_startDelay / 60);
	}
	// �t�H���g�T�C�Y��W���ɖ߂�
	SetFontSize(20);

	if (m_startDelay / 60 != 4)
	{
		if (!m_isOnlyOnceSE)
		{
			PlaySoundMem(m_hCountDown, DX_PLAYTYPE_BACK);
			m_isOnlyOnceSE = true;
		}

		m_pPlayer->DrawSpawnPos();

		if (m_isTutorial) DrawHowTo(Game::kScreenWidthHalf - 193, Game::kScreenHeightHalf - 100);
	}

	if (m_startDelay / 60 <= 2)
	{
		if (m_pPlayer->IsMoveRight())
		{
			temp = "��";
		}
		else
		{
			temp = "��";
		}

		if ((m_textTimer / 10) % 2 != 0)
		{
			SetFontSize(40);
			DrawFormatString(static_cast<int>(m_pPlayer->GetPos().x) + 5, 
				static_cast<int>(m_pPlayer->GetPos().y) - 50,
				0xff0000, "%s", temp.c_str());
			SetFontSize(0);
		}
		m_textTimer++;
	}
}

// �X�e�[�W�N���A���̏���
void SceneMain::OnStageClear(NextSceneState& nextScene)
{
	// �X�e�[�W�P�O or ���K���[�h �̏ꍇ�̏���
	if (m_pStage->GetStageState() == StageState::tenthStage || m_isPracticeMode)
	{
		// �`�������W���[�h�̏ꍇ
		if (m_isArcadeMode)
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
		m_fadeCount = 150;
		m_startDelay = 180;
		m_updateFunc = &SceneMain::StartDelayUpdate;	// �t�F�[�h���������s����
		// ���̃X�e�[�W��Ԃ��Z�b�g
		m_pStage->SetNextStageState();
		// �Q�[���X�^�[�g���̏�����
		OnGameStart();
	}
}

// �ʏ펞�̍X�V����
void SceneMain::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	// �Q�[��BGM�Đ�
	PlayGameLoopBgm();

	if (m_attemptDrawTime > 0)
	{
		m_attemptDrawTime--;
		if ((m_attemptDrawTime / 60) < 2)
		{
			m_attemptDrawNum -= 10;
		}
	}

	// escape�L�[�������ꂽ�ꍇ
	if (input.IsTriggered(InputType::pause))
	{
		m_isPause = true;
		StopSoundMem(m_hPlayBgm);
	}

	// R�L�[�������ꂽ�ꍇ
	if (input.IsTriggered(InputType::retry))
	{
		OnRetry();
	}

	// �v���C���[�̍X�V����
	m_pPlayer->Update(input);

	// �X�e�[�W�̍X�V����
	m_pStage->Update();

	// �X�e�[�W�N���A�̃t���O�� true ���ǂ���
	if (m_pPlayer->IsStageClear())
	{
		// �X�e�[�W�N���A���̏���
		OnStageClear(nextScene);
	}

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_pPlayer->IsDead())
	{
		OnDead();
		return;
	}
}

// �X�^�[�g�J�E���g�_�E�����̍X�V����
void SceneMain::StartDelayUpdate(const InputState& input, NextSceneState& nextScene)
{
	// �X�^�[�g�x���𖈃t���[�����炷
	m_startDelay--;
	// �X�^�[�g�x���� 1 �ȏ�̏ꍇ�����I��
	if (m_startDelay < 0)
	{
		m_updateFunc = &SceneMain::NormalUpdate;
		m_startDelay = 0;
		m_fadeCount = 0;
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
		m_updateFunc = &SceneMain::StartDelayUpdate;
	}
}

void SceneMain::SceneEndUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount += 5;
	ChangeVolumeSoundMem(255 - m_fadeCount, m_hPlayBgm);

	if (m_fadeCount > 255)
	{
		m_isEnd = true;
	}
}

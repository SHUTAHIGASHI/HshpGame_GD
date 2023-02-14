#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"
#include <vector>

enum class NextSceneState
{
	Empty,
	nextMenu,
	nextHelp,
	nextRanking,
	nextStageSelect,
	nextGameMain,
	nextClear
};

enum class ObjectType
{
	Empty,
	GoalGate,
	Block,
	JumpRing,
	JumpPad,
	Spike,
	GravityRing,
	DashRing,
	ReverseRing,
	End
};

namespace Game
{
	// �V�X�e����{�ݒ� //
#ifdef _DEBUG
	// �E�B���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// �E�B���h�E��
	const char* const kTitleText = "SquareJumper";
	// �E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// �J���[���[�h
	constexpr int kColorDepth = 32;
	
	// �摜�f�[�^
	const char* const kPlayerImg = "imagedata/PlayerImg.png";
	const char* const kPlayerDeathEffectImg = "imagedata/deathEffect.png";

	const char* const kObjectSpikeImg = "imagedata/ObjectSpike.png";

	// ��̃t�H���g�T�C�Y
	constexpr int kFontSize = 60;

	// �Q�[���̊�{�ݒ� //
	// �v���C���[�̊�{�ݒ�
	constexpr float kBlockSize = 48.0f;

	// ��{�ړ����x
	constexpr float kMoveSpeed = 7.0f;

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr float kStageUpperLimit = Game::kBlockSize * 4;
	constexpr float kStageLowerLimit = Game::kBlockSize * 20;
	
	// �X�e�[�W������
	constexpr int kScreenWidthNum = static_cast<int>(Game::kScreenWidth / Game::kBlockSize);
	constexpr int kScreenWidthTripleNum = static_cast<int>(Game::kScreenWidthTriple / Game::kBlockSize);
	// �X�e�[�W�c����
	constexpr int kScreenHeightNum = static_cast<int>(Game::kScreenHeight / Game::kBlockSize);
	constexpr int kScreenHeightTripleNum = static_cast<int>(Game::kScreenHeightTriple / Game::kBlockSize);
}
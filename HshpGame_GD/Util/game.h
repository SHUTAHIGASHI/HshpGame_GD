#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"
#include <vector>

enum class NextSceneState
{
	Empty,
	nextTitle,
	nextDemo,
	nextHowTo,
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
	const char* const kPlayerImg = "imagedata/PlayerImage.png";
	const char* const kPlayerDeathEffectImg = "imagedata/deathEffect.png";
	const char* const kObjectSpikeImg = "imagedata/ObjectSpike.png";
	const char* const kPortalImg = "imagedata/OrangePortal.png";
	const char* const kBlockImg = "imagedata/Tileset.png";
	const char* const kJumpPadImg = "imagedata/JumpPad.png";
	const char* const kBgImg = "imagedata/Bg.png";
	const char* const kPadImg = "imagedata/PadImg.png";

	// ���y�f�[�^
	const char* const kDeathSound = "soundData/deathSound.mp3";
	const char* const kPracBgm = "soundData/pracmode.ogg";
	const char* const kChallengeBgm = "soundData/ElectromanAdventuresV2.mp3";

	// ��̃t�H���g�T�C�Y
	constexpr int kFontSize = 60;

	// �p�b�h�摜�`�b�v�T�C�Y
	constexpr int kPadChipSize = 16;

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

	// �p�[�e�B�N���p
	constexpr int kParticleNum = 4096;
}
#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"
#include <vector>

enum class ObjectType
{
	Empty,
	Block,
	JumpRing,
	End
};

namespace Game
{
	// �V�X�e����{�ݒ� //
	// �E�B���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
	// �E�B���h�E��
	const char* const kTitleText = "GxxxxxxyDxxh";
	// �E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;

	// �J���[���[�h
	constexpr int kColorDepth = 32;
	
	// ��̃t�H���g�T�C�Y
	constexpr int kFontSize = 60;

	// �Q�[���̊�{�ݒ� //
	// �v���C���[�̊�{�ݒ�
	constexpr float kBlockSize = 48.0f;
	// ��{�ړ����x
	constexpr float kMoveSpeed = 7.0f;

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr float kStageUpperLimit = Game::kBlockSize * 4;
	constexpr float kStageLowerLimit = Game::kBlockSize * 18;
	// �X�e�[�W����
	constexpr int kScreenWidthNum = static_cast<int>(Game::kScreenWidth / Game::kBlockSize);
	// �X�e�[�W�c��
	constexpr int kScreenHeightNum = static_cast<int>(Game::kScreenHeight / Game::kBlockSize);
}
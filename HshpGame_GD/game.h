#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"

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
	constexpr float kMoveSpeed = 5.0f;

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr int kStageUpperLimit = Game::kBlockSize * 4;
	constexpr int kStageLowerLimit = Game::kBlockSize * 18;
	// �X�e�[�W����
	constexpr int kScreenWidthNum = Game::kScreenWidth / Game::kBlockSize;
	// �X�e�[�W�c��
	constexpr int kScreenHeightNum = Game::kScreenHeight / Game::kBlockSize;
}
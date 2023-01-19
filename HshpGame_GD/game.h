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
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr int kStageUpperLimit = 100;
	constexpr int kStageLowerLimit = 620;

	// �J���[���[�h
	constexpr int kColorDepth = 32;
	
	// ��̃t�H���g�T�C�Y
	constexpr int kFontSize = 60;

	// �Q�[���̊�{�ݒ� //
	// �v���C���[�̊�{�ݒ�
	constexpr float kBlockSize = 48.0f;
	// ��{�ړ����x
	constexpr float kMoveSpeed = 7.0f;
}
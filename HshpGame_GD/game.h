#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"

namespace Game
{
	// システム基本設定 //
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
	// ウィンドウ名
	const char* const kTitleText = "GxxxxxxyDxxh";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;

	// ゲームのステージサイズ
	constexpr int kStageUpperLimit = 100;
	constexpr int kStageLowerLimit = 620;

	// カラーモード
	constexpr int kColorDepth = 32;
	
	// 基準のフォントサイズ
	constexpr int kFontSize = 60;

	// ゲームの基本設定 //
	// プレイヤーの基本設定
	constexpr float kBlockSize = 48.0f;
	// 基本移動速度
	constexpr float kMoveSpeed = 7.0f;
}
#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"
#include <vector>

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
	// システム基本設定 //
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
	// ウィンドウ名
	const char* const kTitleText = "GxxxxxxyDxxh";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// カラーモード
	constexpr int kColorDepth = 32;
	
	// 画像データ
	const char* const kPlayerImg = "imagedata/PlayerImage.png";
	const char* const kPlayerDeathEffectImg = "imagedata/deathEffect.png";

	const char* const kObjectSpikeImg = "imagedata/ObjectSpike.png";

	// 基準のフォントサイズ
	constexpr int kFontSize = 60;

	// ゲームの基本設定 //
	// プレイヤーの基本設定
	constexpr float kBlockSize = 48.0f;

	// 基本移動速度
	constexpr float kMoveSpeed = 7.0f;

	// ゲームのステージサイズ
	constexpr float kStageUpperLimit = Game::kBlockSize * 4;
	constexpr float kStageLowerLimit = Game::kBlockSize * 20;
	
	// ステージ横幅数
	constexpr int kScreenWidthNum = static_cast<int>(Game::kScreenWidth / Game::kBlockSize);
	constexpr int kScreenWidthTripleNum = static_cast<int>(Game::kScreenWidthTriple / Game::kBlockSize);
	// ステージ縦幅数
	constexpr int kScreenHeightNum = static_cast<int>(Game::kScreenHeight / Game::kBlockSize);
	constexpr int kScreenHeightTripleNum = static_cast<int>(Game::kScreenHeightTriple / Game::kBlockSize);
}
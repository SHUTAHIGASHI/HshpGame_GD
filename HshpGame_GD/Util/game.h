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
	// システム基本設定 //
#ifdef _DEBUG
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// ウィンドウ名
	const char* const kTitleText = "SquareJumper";
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
	const char* const kPlayerImg = "Data/imagedata/cube.png";
	const char* const kPlayerDeathEffectImg = "Data/imagedata/deathEffect.png";
	const char* const kObjectSpikeImg = "Data/imagedata/ObjectSpike.png";
	const char* const kPortalImg = "Data/imagedata/OrangePortal.png";
	const char* const kBlockImg = "Data/imagedata/Tileset.png";
	const char* const kJumpPadImg = "Data/imagedata/JumpPad.png";
	const char* const kBgImg = "Data/imagedata/Bg.png";
	const char* const kPadImg = "Data/imagedata/PadImg.png";

	// 音データ
	const char* const kSelectSound = "Data/soundData/Select.mp3";

	// 音楽データ
	const char* const kDeathSound = "Data/soundData/DeathSound.mp3";
	const char* const kArcadeBgm = "Data/soundData/Arcade.mp3";
	const char* const kPracBgm = "Data/soundData/Pracmode.wav";
	const char* const kChallengeBgm = "Data/soundData/Challenge.mp3";

	// 基準のフォントサイズ
	constexpr int kFontSize = 60;

	// パッド画像チップサイズ
	constexpr int kPadChipSize = 16;

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

	// パーティクル用
	constexpr int kParticleNum = 4096;
}
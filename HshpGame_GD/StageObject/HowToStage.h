#pragma once

#include "Game.h"
#include "ObjectGoalGate.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectDashRing.h"
#include "ObjectReverseRing.h"

class HowToPlayer;

enum class HowToStageState
{
	CubeTest,
	JumpRingTest,
	GravityRingTest,
	DashRingTest,
	RevRingTest,
	End
};

class HowToStage
{
public:
	HowToStage();
	~HowToStage() {}

	void SetPlayer(HowToPlayer* player) { m_pHPlayer = player; }

	void Init(int hSpike, int hBg, int hPortal, int hIcon);

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType& object);

	bool IsUnder(const Vec2 playerPos, int H, int W, float& tempPos);

	bool IsTop(const Vec2 playerPos, int H, int W, float& tempPos);

	// ステージ情報の変更
	void StageManage();

	// 選んだステージをセット
	void SetSelectedStage(HowToStageState stage) { m_stageState = stage; }
	// 各ステージのセット
	void SetNextStageState();
	// ステージを一番最初にセット
	void SetFirstStage() { m_stageState = HowToStageState::CubeTest; }

	//ステージの状態を確保
	HowToStageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	// メンバ関数ポインタ
	using m_tUpdateFunc = void (HowToStage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	ObjectBlock m_ObjectBlock[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectSpike m_ObjectSpike[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpRing m_ObjectJumpRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpPad m_ObjectJumpPad[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectGravityRing m_ObjectGravityRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectDashRing m_ObjectDashRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectReverseRing m_ObjectReverseRing[Game::kScreenHeightNum][Game::kScreenWidthNum];

	HowToPlayer* m_pHPlayer;

	// ステージ管理用変数
	HowToStageState m_stageState;
	// ステージ管理用二次元配列
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthNum];

	// 背景
	int m_hBg;
	int m_hBlock;
};


#pragma once

#include "Game.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectGoalGate.h"

class PlayerCube;

enum class StageState
{
	debug,
	firstStage,
	secondStage,
	thirdStage,
	End
};

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void SetPlayer(PlayerCube* cube) { m_pCube = cube; }
	
	void Init(int hSpike);

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType &object);

	bool IsUnder(const Vec2 playerPos, int H, int W, float &tempPos);

	// 各ステージのセット
	void SetSecondStage() { m_stageState = StageState::secondStage; }
	void SetThirdStage() { m_stageState = StageState::thirdStage; }

	bool SetCanScroll() { m_canScroll = true; }

	//ステージの状態を確保
	StageState GetStageState() const { return m_stageState; }

private:
	ObjectBlock m_ObjectBlock[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectSpike m_ObjectSpike[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectJumpRing m_ObjectJumpRing[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectJumpPad m_ObjectJumpPad[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectGravityRing m_ObjectGravityRing[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectGoalGate m_ObjectGoalGate[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	
	/*ObjectBlock m_ObjectBlock[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectSpike m_ObjectSpike[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpRing m_ObjectJumpRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpPad m_ObjectJumpPad[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectGravityRing m_ObjectGravityRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectGoalGate m_ObjectGoalGate[Game::kScreenHeightNum][Game::kScreenWidthNum];*/

	PlayerCube* m_pCube;

	// ステージ管理用変数
	StageState m_stageState;
	// ステージ管理用二次元配列
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];

	// スクロール用変数
	int m_scroll;
	int m_scrollAcc;
	bool m_canScroll;

	void NormalUpdate();

	void ScrollUpdate();

	// メンバ関数ポインタ
	using m_tUpdateFunc = void (Stage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
};


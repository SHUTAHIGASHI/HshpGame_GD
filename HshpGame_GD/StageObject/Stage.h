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

class Player;

enum class StageState
{
	firstStage,
	secondStage,
	thirdStage,
	fourthStage,
	fifthStage,
	sixthStage,
	seventhStage,
	eighthStage,
	ninthStage,
	tenthStage,
	End
};

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void SetPlayer(Player* player) { m_pPlayer = player; }
	
	void Init(int hSpike, int hBg, int hPortal, int hBlock);

	void InitStage(int hSpike, int hPortal, int hBlock);

	void End();

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType &object);

	bool IsUnder(float &tempPos);

	bool IsTop(float& tempPos);

	// ステージ情報の変更
	void StageManage();

	// 選んだステージをセット
	void SetSelectedStage(StageState stage) { m_stageState = stage; }
	// 各ステージのセット
	void SetNextStageState();
	// ステージを一番最初にセット
	void SetFirstStage() { m_stageState = StageState::firstStage; }

	// スクロール処理に関して
	bool SetCanScroll() { m_canScroll = true; }
	void ChangeScroll() { m_scrollAcc *= -1; }

	int GetScroll() const { return m_scroll; }

	//ステージの状態を確保
	StageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	void ScrollUpdate();

	// メンバ関数ポインタ
	using m_tUpdateFunc = void (Stage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	std::vector<ObjectGoalGate> m_ObjectGoalGate;
	std::vector<ObjectBlock> m_ObjectBlock;
	std::vector<ObjectJumpRing> m_ObjectJumpRing;
	std::vector<ObjectJumpPad> m_ObjectJumpPad;
	std::vector<ObjectSpike> m_ObjectSpike;
	std::vector<ObjectGravityRing> m_ObjectGravityRing;
	std::vector<ObjectDashRing> m_ObjectDashRing;
	std::vector<ObjectReverseRing> m_ObjectReverseRing;

	Player* m_pPlayer;

	// ステージ管理用変数
	StageState m_stageState;
	// ステージ管理用二次元配列
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];

	// 座標数値の一時保存
	int m_tempNum;

	// スクロール用変数
	int m_scroll;
	int m_scrollAcc;
	bool m_canScroll;

	// 背景
	int m_hBg;
};


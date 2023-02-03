#pragma once

#include "Game.h"
#include "ObjectGoalGate.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectDashRing.h"

class Player;

enum class StageState
{
	debug,
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
	
	void Init(int hSpike, int hBg);

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType &object);

	bool IsUnder(const Vec2 playerPos, int H, int W, float &tempPos);

	bool IsTop(const Vec2 playerPos, int H, int W, float& tempPos);

	// �X�e�[�W���̕ύX
	void StageManage();

	// �e�X�e�[�W�̃Z�b�g
	void ChangeStageState();
	void SetSecondStage() { m_stageState = StageState::secondStage; }
	void SetThirdStage() { m_stageState = StageState::thirdStage; }

	bool SetCanScroll() { m_canScroll = true; }

	//�X�e�[�W�̏�Ԃ��m��
	StageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	void ScrollUpdate();

	// �����o�֐��|�C���^
	using m_tUpdateFunc = void (Stage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	ObjectGoalGate m_ObjectGoalGate[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectBlock m_ObjectBlock[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectSpike m_ObjectSpike[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectJumpRing m_ObjectJumpRing[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectJumpPad m_ObjectJumpPad[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectGravityRing m_ObjectGravityRing[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];
	ObjectDashRing m_ObjectDashRing[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];

	Player* m_pPlayer;

	// �X�e�[�W�Ǘ��p�ϐ�
	StageState m_stageState;
	// �X�e�[�W�Ǘ��p�񎟌��z��
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];

	// �X�N���[���p�ϐ�
	int m_scroll;
	int m_scrollAcc;
	bool m_canScroll;

	// �w�i
	int m_hBg;
};


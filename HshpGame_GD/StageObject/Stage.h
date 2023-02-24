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

	// �X�e�[�W���̕ύX
	void StageManage();

	// �I�񂾃X�e�[�W���Z�b�g
	void SetSelectedStage(StageState stage) { m_stageState = stage; }
	// �e�X�e�[�W�̃Z�b�g
	void SetNextStageState();
	// �X�e�[�W����ԍŏ��ɃZ�b�g
	void SetFirstStage() { m_stageState = StageState::firstStage; }

	// �X�N���[�������Ɋւ���
	bool SetCanScroll() { m_canScroll = true; }
	void ChangeScroll() { m_scrollAcc *= -1; }

	int GetScroll() const { return m_scroll; }

	//�X�e�[�W�̏�Ԃ��m��
	StageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	void ScrollUpdate();

	// �����o�֐��|�C���^
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

	// �X�e�[�W�Ǘ��p�ϐ�
	StageState m_stageState;
	// �X�e�[�W�Ǘ��p�񎟌��z��
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];

	// ���W���l�̈ꎞ�ۑ�
	int m_tempNum;

	// �X�N���[���p�ϐ�
	int m_scroll;
	int m_scrollAcc;
	bool m_canScroll;

	// �w�i
	int m_hBg;
};


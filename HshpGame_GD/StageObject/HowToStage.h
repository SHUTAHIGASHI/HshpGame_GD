#pragma once

#include "Game.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectDashRing.h"
#include "ObjectReverseRing.h"
#include <vector>

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

	void InitStage(int hSpike, int hPortal, int hBlock);

	void End();

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType& object);

	bool IsUnder(const Vec2 playerPos, int H, int W, float& tempPos);

	bool IsTop(const Vec2 playerPos, int H, int W, float& tempPos);

	// �X�e�[�W���̕ύX
	void StageManage();

	// �I�񂾃X�e�[�W���Z�b�g
	void SetSelectedStage(HowToStageState stage) { m_stageState = stage; }
	// �e�X�e�[�W�̃Z�b�g
	void SetNextStageState();
	// �X�e�[�W����ԍŏ��ɃZ�b�g
	void SetFirstStage() { m_stageState = HowToStageState::CubeTest; }

	//�X�e�[�W�̏�Ԃ��m��
	HowToStageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	// �����o�֐��|�C���^
	using m_tUpdateFunc = void (HowToStage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	std::vector<ObjectBlock> m_ObjectBlock;
	std::vector<ObjectJumpRing> m_ObjectJumpRing;
	std::vector<ObjectJumpPad> m_ObjectJumpPad;
	std::vector<ObjectSpike> m_ObjectSpike;
	std::vector<ObjectGravityRing> m_ObjectGravityRing;
	std::vector<ObjectDashRing> m_ObjectDashRing;
	std::vector<ObjectReverseRing> m_ObjectReverseRing;

	HowToPlayer* m_pHPlayer;

	// �X�e�[�W�Ǘ��p�ϐ�
	HowToStageState m_stageState;
	// �X�e�[�W�Ǘ��p�񎟌��z��
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthNum];

	int m_tempNum;

	// �w�i
	int m_hBg;
};


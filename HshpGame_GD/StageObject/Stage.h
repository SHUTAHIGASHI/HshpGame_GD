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
	tutrialCube,
	tutrialJump,
	tutrialGravity,
	tutrialDash,
	tutrialRev,
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
	Empty
};

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void SetPlayer(Player* player) { m_pPlayer = player; }
	
	void Init(int hSpike, int hBg, int hPortal, int hBlock, int hJumpPad);

	void InitStage(int hSpike, int hPortal, int hBlock, int hJumpPad);

	void End();

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, ObjectType &object);

	bool IsUnder(float &tempPos);

	bool IsTop(float& tempPos);

	// ���ׂẴI�u�W�F�N�g���N���A
	void ClearAllObject();

	// ���݂̃X�e�[�W���̏�����
	void ResetStage();
	// ���݂̃X�e�[�W���̕ύX
	void StageManage();

	// �`���[�g���A���X�e�[�W���Z�b�g1
	void SetTutorialStage() { m_stageState = StageState::tutrialCube; }
	// �I�񂾃X�e�[�W���Z�b�g
	void SetSelectedStage(StageState stage) { m_stageState = stage; }
	// ���̃X�e�[�W�̃Z�b�g
	void SetNextStageState();
	// �X�e�[�W����ԍŏ��ɃZ�b�g
	void SetFirstStage() { m_stageState = StageState::firstStage; }

	// �X�N���[�������Ɋւ���
	bool IsScrollStage() const { return m_isScrollStage; }
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
	// �X�N���[������X�e�[�W���ǂ���
	bool m_isScrollStage;
	// ���݃X�N���[�������ǂ���
	bool m_isScroll;
	// �X�N���[�����l
	int m_scroll;
	// �X�N���[���̕ω����x
	int m_scrollAcc;

	// �w�i
	int m_hBg;
};


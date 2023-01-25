#include "Stage.h"
#include "game.h"
#include "playerCube.h"

namespace
{
	//�}�b�v�f�[�^
	// 1 �S�[�� / 2 �u���b�N / 3 �W�����v�����O / 4 �W�����v�p�b�h 
	// 5 �X�p�C�N / 6 �O���r�e�B�����O / 7 �O���r�e�B�p�b�h / 8  /

	// �X�e�[�W�P
	int m_stage_s[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,0,0,0,0,4,0,2,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,5,5,0,2,0,0,0,0,0,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,3,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,2,2,2,2,2},
		{0,0,0,0,3,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,5,5,0,0,0,5,5,5,0,5,5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0},
		{0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,4,0,0,0,0,5,0,0,0,0,4,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,5,0,4,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
		// �X�e�[�W�n��
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	// �X�e�[�W�Q
	int m_stage_first[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		// �X�e�[�W�n��
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};
}

Stage::Stage() :
	m_pCube(nullptr)
{

}

void Stage::Init()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			float blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;
			
			if (m_stage_first[i][j] == 1) m_ObjectGoalGate[i][j].Init(blockPosX, blockPosY);
			if (m_stage_first[i][j] == 2) m_ObjectBlock[i][j].Init(blockPosX, blockPosY);
			if (m_stage_first[i][j] == 3) m_ObjectJumpRing[i][j].Init(blockPosX, blockPosY);
			if (m_stage_first[i][j] == 4) m_ObjectJumpPad[i][j].Init(blockPosX, blockPosY);
			if (m_stage_first[i][j] == 5) m_ObjectSpike[i][j].Init(blockPosX, blockPosY);
			if (m_stage_first[i][j] == 6) m_ObjectGravityRing[i][j].Init(blockPosX, blockPosY);
			if (m_stage_first[i][j] == 7) m_ObjectGravityPad[i][j].Init(blockPosX, blockPosY);
		}
	}
}

void Stage::Update()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_ObjectJumpRing[i][j].Update();
			m_ObjectGravityRing[i][j].Update();
		}
	}
}

void Stage::Draw()
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			int drawPosX = 0, drawPosY = 0;
			drawPosX = static_cast<int>(j * Game::kBlockSize);
			drawPosY = static_cast<int>(i * Game::kBlockSize);
			
			// �f�o�b�N�p����
			DrawBox(drawPosX, drawPosY, drawPosX + static_cast<int>(Game::kBlockSize), drawPosY + static_cast<int>(Game::kBlockSize), 0xFFFFFF, false);

			// �X�e�[�W�M�~�b�N�̕`��
			if (m_stage_first[i][j] == 1) m_ObjectGoalGate[i][j].Draw();
			if (m_stage_first[i][j] == 2) m_ObjectBlock[i][j].Draw();
			if (m_stage_first[i][j] == 3) m_ObjectJumpRing[i][j].Draw();
			if (m_stage_first[i][j] == 4) m_ObjectJumpPad[i][j].Draw();
			if (m_stage_first[i][j] == 5) m_ObjectSpike[i][j].Draw();
			if (m_stage_first[i][j] == 6) m_ObjectGravityRing[i][j].Draw();
			if (m_stage_first[i][j] == 7) m_ObjectGravityPad[i][j].Draw();
		}
	}
}

// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��`�F�b�N
bool Stage::CollisionCheck(Vec2 playerPos, int H, int W, ObjectType &object)
{
	// �������Ă���ꍇ�Atrue��Ԃ�
	// �u���b�N�̓����蔻��
	if (m_ObjectBlock[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectBlock[H][W].GetLeft() &&
		m_ObjectBlock[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectBlock[H][W].GetTop())
	{
		object = ObjectType::Block;
		return true;
	}
	// �W�����v�����O�̓����蔻��
	if (m_ObjectJumpRing[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectJumpRing[H][W].GetLeft() &&
		m_ObjectJumpRing[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectJumpRing[H][W].GetTop())
	{
		object = ObjectType::JumpRing;
		return true;
	}
	// �W�����v�p�b�h�̓����蔻��
	if (m_ObjectJumpPad[H][W].GetRight() - 5 > playerPos.x &&
		playerPos.x + Game::kBlockSize > m_ObjectJumpPad[H][W].GetLeft() + 5 &&
		m_ObjectJumpPad[H][W].GetBottom() > playerPos.y &&
		playerPos.y + Game::kBlockSize > m_ObjectJumpPad[H][W].GetTop() + Game::kBlockSize - (Game::kBlockSize / 4))
	{
		object = ObjectType::JumpPad;
		return true;
	}
	// �X�p�C�N�̓����蔻��
	if (m_ObjectSpike[H][W].GetRight() > playerPos.x &&
		playerPos.x + Game::kBlockSize > m_ObjectSpike[H][W].GetLeft() &&
		m_ObjectSpike[H][W].GetBottom() > playerPos.y &&
		playerPos.y + Game::kBlockSize > m_ObjectSpike[H][W].GetTop())
	{
		object = ObjectType::Spike;
		return true;
	}
	// �O���r�e�B�����O�̓����蔻��
	if (m_ObjectGravityRing[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectGravityRing[H][W].GetLeft() &&
		m_ObjectGravityRing[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectGravityRing[H][W].GetTop())
	{
		object = ObjectType::GravityRing;
		return true;
	}
	// �O���r�e�B�p�b�h�̓����蔻��
	if (m_ObjectGravityPad[H][W].GetRight() - 5 > playerPos.x &&
		playerPos.x + Game::kBlockSize > m_ObjectGravityPad[H][W].GetLeft() + 5 &&
		m_ObjectGravityPad[H][W].GetBottom() > playerPos.y &&
		playerPos.y + Game::kBlockSize > m_ObjectGravityPad[H][W].GetTop() + Game::kBlockSize - (Game::kBlockSize / 4))
	{
		object = ObjectType::GravityPad;
		return true;
	}
	// �S�[���Q�[�g�̔���
	if (m_ObjectGoalGate[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectGoalGate[H][W].GetLeft() &&
		m_ObjectGoalGate[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectGoalGate[H][W].GetTop())
	{
		object = ObjectType::GoalGate;
		return true;
	}

	// �������Ă��Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

// �I�u�W�F�N�g���v���C���[�̉��ɂ��邩�ǂ���
bool Stage::IsUnder(Vec2 playerPos, float &tempPos,  int H, int W)
{	
	// �u���b�N�����݂���ꍇ
	if(m_stage_first[H][W] == 2)
	{
		if (!m_pCube->IsRevGravity())
		{
			// �v���C���[�̒��S�A�u���b�N�̏�ʂł̔���
			// ���ɂ���ꍇ�Atrue��Ԃ�
			if (m_ObjectBlock[H][W].GetPos().y > playerPos.y + (Game::kBlockSize / 2))
			{
				// �u���b�N�̍��W����
				tempPos = m_ObjectBlock[H][W].GetPos().y;
				return true;
			}
		}
		else
		{
			if (m_ObjectBlock[H][W].GetPos().y < playerPos.y + (Game::kBlockSize / 2))
			{
				// �u���b�N�̍��W����
				tempPos = m_ObjectBlock[H][W].GetPos().y + Game::kBlockSize;
				return true;
			}
		}
	}
	
	// ���ł͂Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

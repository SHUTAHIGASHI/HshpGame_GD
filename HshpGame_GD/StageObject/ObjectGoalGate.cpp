#include "ObjectGoalGate.h"

ObjectGoalGate::ObjectGoalGate() :
	m_countFrame(0),
	m_hPortal(-1),
	m_imgX(0),
	m_imgY(0)
{
}

void ObjectGoalGate::Init(int hPortal)
{
	m_IsExist = false;

	m_hPortal = hPortal;
	
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize * 3;
}

void ObjectGoalGate::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectGoalGate::Update()
{
	if (!m_IsExist) return;

	m_countFrame++;
}

void ObjectGoalGate::Draw()
{
	if (!m_IsExist) return;

	m_drawFrame += m_countFrame % 2;
	if (m_drawFrame > 8) m_drawFrame = 0;
	
	m_imgX = static_cast<int>(m_drawFrame * Game::kBlockSize);
	m_imgY = 0;
	int imgW = 0, imgH = 0;
	imgW = Game::kBlockSize;
	imgH = Game::kBlockSize;

	DrawRectExtendGraphF(m_pos.x, m_pos.y,
		m_pos.x + Game::kBlockSize, m_pos.y + (Game::kBlockSize * 3), 
		m_imgX, m_imgY, imgW, imgH, 
		m_hPortal, true);
}

bool ObjectGoalGate::CollisionCheck(Vec2 player, int resizeScale)
{
	if (!m_IsExist) return false;

	// �X�p�C�N�̓����蔻��
	if (GetRight() > player.x &&
		player.x + Game::kBlockSize > GetLeft() &&
		GetBottom() + resizeScale > player.y &&
		player.y + Game::kBlockSize > GetTop())
	{
		return true;
	}

	return false;
}

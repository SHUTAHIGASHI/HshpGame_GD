#include "MapObject.h"

MapObject::MapObject() :
	m_pos()
{
}

void MapObject::Init()
{
	m_pos.x = Game::kScreenWidth - Game::kBlockSize;
	m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
}

void MapObject::Update()
{
	m_pos.x += -Game::kMoveSpeed;

	if (m_pos.x + Game::kBlockSize <= 0) m_pos.x = Game::kScreenWidth + Game::kBlockSize;
}

void MapObject::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

bool MapObject::CollisionCheck(float X, float Y)
{	
	// �������Ă��Ȃ��ꍇ�������X�L�b�v
	if (GetRight() <= X) return false;
	if (X + Game::kBlockSize <= GetLeft()) return false;
	if (GetBottom() <= Y) return false;
	if (Y + Game::kBlockSize <= GetTop()) return false;
	
	// �������Ă���ꍇ�v���C���[�����S����ɂ���
	return true;
}

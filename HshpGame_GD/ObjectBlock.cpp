#include "ObjectBlock.h"

ObjectBlock::ObjectBlock()
{
}

void ObjectBlock::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;
}

void ObjectBlock::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectBlock::Update()
{
	//m_pos.x += -Game::kMoveSpeed;

	if (m_pos.x + Game::kBlockSize <= 0) m_pos.x = Game::kScreenWidth + Game::kBlockSize;
}

void ObjectBlock::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
	//DrawTriangle(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

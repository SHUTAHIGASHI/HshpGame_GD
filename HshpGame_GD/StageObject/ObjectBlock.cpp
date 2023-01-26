#include "ObjectBlock.h"

ObjectBlock::ObjectBlock()
{
}

void ObjectBlock::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectBlock::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectBlock::Update()
{
}

void ObjectBlock::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0x4169e1, true);
	//DrawTriangle(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

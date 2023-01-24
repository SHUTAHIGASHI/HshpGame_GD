#include "ObjectSpike.h"

ObjectSpike::ObjectSpike()
{
}

void ObjectSpike::Init(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectSpike::Update()
{
}

void ObjectSpike::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0x0000FF, true);
	//DrawTriangle(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

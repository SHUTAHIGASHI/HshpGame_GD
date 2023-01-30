#include "ObjectSpike.h"

ObjectSpike::ObjectSpike()
{
}

void ObjectSpike::Init(int hSpike)
{
	m_hObjectImg = hSpike;

	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectSpike::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectSpike::Update()
{
}

void ObjectSpike::Draw(int scroll)
{
	//DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xff0000, true);
	DrawRotaGraph(GetCenterX() - scroll, GetCenterY(), 1, 0, m_hObjectImg, true, false);

	//DrawTriangle(GetCenterX(), m_pos.y, m_pos.x, m_pos.y + Game::kBlockSize, GetRight(), m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

#include "ObjectSpike.h"

ObjectSpike::ObjectSpike()
{
}

void ObjectSpike::Init(int hSpike)
{
	m_IsExist = false;
	
	m_hObjectImg = hSpike;

	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectSpike::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectSpike::Update()
{
}

void ObjectSpike::Draw()
{
	if (!m_IsExist) return;

	DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, 0, m_hObjectImg, true, false);
}

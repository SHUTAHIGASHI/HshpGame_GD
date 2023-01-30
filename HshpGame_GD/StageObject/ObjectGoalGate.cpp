#include "ObjectGoalGate.h"

ObjectGoalGate::ObjectGoalGate()
{
}

void ObjectGoalGate::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectGoalGate::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectGoalGate::Update()
{
}

void ObjectGoalGate::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0x00ff00, true);
}

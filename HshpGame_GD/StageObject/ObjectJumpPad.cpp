#include "ObjectJumpPad.h"

ObjectJumpPad::ObjectJumpPad()
{
}

void ObjectJumpPad::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectJumpPad::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectJumpPad::Update()
{

}

void ObjectJumpPad::Draw()
{
	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY() + Game::kBlockSize - (Game::kBlockSize / 4)), static_cast<int>(Game::kBlockSize / 2 - 2), 0xffff00, true);
}

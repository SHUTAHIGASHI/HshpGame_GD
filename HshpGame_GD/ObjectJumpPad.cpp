#include "ObjectJumpPad.h"

ObjectJumpPad::ObjectJumpPad()
{
}

void ObjectJumpPad::Init(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectJumpPad::Update()
{

}

void ObjectJumpPad::Draw()
{
	DrawCircle(GetCenterX(), GetCenterY() + Game::kBlockSize - (Game::kBlockSize / 4), Game::kBlockSize / 2, 0xffff00, true);
}

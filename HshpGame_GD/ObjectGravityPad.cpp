#include "ObjectGravityPad.h"

ObjectGravityPad::ObjectGravityPad()
{
}

void ObjectGravityPad::Init(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectGravityPad::Update()
{

}

void ObjectGravityPad::Draw()
{
	DrawCircle(GetCenterX(), GetCenterY() + Game::kBlockSize - (Game::kBlockSize / 4), Game::kBlockSize / 2 - 2, 0x00bfff, true);
}

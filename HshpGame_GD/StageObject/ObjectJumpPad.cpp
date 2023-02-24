#include "ObjectJumpPad.h"

ObjectJumpPad::ObjectJumpPad() :
	countFrame(0)
{
}

void ObjectJumpPad::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;
}

void ObjectJumpPad::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectJumpPad::Update()
{
	//countFrame++;
}

void ObjectJumpPad::Draw()
{
	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY() + Game::kBlockSize - (Game::kBlockSize / 4)),
		static_cast<int>(Game::kBlockSize / 2 - 2), 0xFFD700, true);
}

bool ObjectJumpPad::CollisionCheck(Vec2 player, int resizeScale)
{
	// “–‚½‚è”»’è
	if (GetRight() - 5> player.x &&
		player.x + Game::kBlockSize > GetLeft() + 5 &&
		GetBottom() > player.y &&
		player.y + Game::kBlockSize > GetTop() + resizeScale)
	{
		return true;
	}

	return false;
}

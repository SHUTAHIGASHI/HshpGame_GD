#include "ObjectJumpPad.h"

ObjectJumpPad::ObjectJumpPad()
{
}

void ObjectJumpPad::Init()
{
	m_IsExist = false;

	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectJumpPad::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectJumpPad::Update()
{

}

void ObjectJumpPad::Draw()
{
	if (!m_IsExist) return;

	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY() + Game::kBlockSize - (Game::kBlockSize / 4)), static_cast<int>(Game::kBlockSize / 2 - 2), 0xFFD700, true);
}

bool ObjectJumpPad::CollisionCheck(Vec2 player, int resizeScale)
{
	if (!m_IsExist) return false;

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

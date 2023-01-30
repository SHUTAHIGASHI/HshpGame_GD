#include "ObjectJumpRing.h"

ObjectJumpRing::ObjectJumpRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectJumpRing::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectJumpRing::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectJumpRing::Update()
{
	circleSize += sizeAcc;
	
	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectJumpRing::Draw(int scroll)
{
	DrawCircle(GetCenterX() - scroll, GetCenterY(), circleSize, 0xffff00, true);
	DrawCircle(GetCenterX() - scroll, GetCenterY(), circleSize + 5, 0xffffff, false);
}

#include "ObjectJumpRing.h"

ObjectJumpRing::ObjectJumpRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectJumpRing::Init(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;

	circleSize = (Game::kBlockSize / 2) - 5;
	sizeAcc = 0.5f;
}

void ObjectJumpRing::Update()
{
	circleSize += sizeAcc;
	
	if (circleSize > Game::kBlockSize - 5) sizeAcc *= -1;
	else if (circleSize < Game::kBlockSize - 10) sizeAcc *= -1;
}

void ObjectJumpRing::Draw()
{
	DrawCircle(GetCenterX(), GetCenterY(), circleSize, 0xffff00, true);
	DrawCircle(GetCenterX(), GetCenterY(), Game::kBlockSize / 2, 0xffffff, false);
}

#include "ObjectGravityRing.h"

ObjectGravityRing::ObjectGravityRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectGravityRing::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;
}

void ObjectGravityRing::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectGravityRing::Update()
{
	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectGravityRing::Draw()
{
	DrawCircle(GetCenterX(), GetCenterY(), circleSize, 0x00bfff, true);
	DrawCircle(GetCenterX(), GetCenterY(), circleSize + 5, 0xffffff, false);
}

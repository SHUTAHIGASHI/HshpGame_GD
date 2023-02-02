#include "ObjectDashRing.h"

ObjectDashRing::ObjectDashRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectDashRing::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectDashRing::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectDashRing::Update()
{
	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectDashRing::Draw()
{
	DrawCircle(GetCenterX(), GetCenterY(), circleSize, 0xdc143c, true);
	DrawCircle(GetCenterX(), GetCenterY(), circleSize + 5, 0xffffff, false);
}

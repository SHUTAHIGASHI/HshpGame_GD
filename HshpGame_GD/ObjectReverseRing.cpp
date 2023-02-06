#include "ObjectReverseRing.h"

ObjectReverseRing::ObjectReverseRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectReverseRing::Init()
{
	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectReverseRing::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectReverseRing::Update()
{
	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectReverseRing::Draw()
{
	DrawCircle(GetCenterX(), GetCenterY(), circleSize, 0x8a2be2, true);
	DrawCircle(GetCenterX(), GetCenterY(), circleSize + 2, 0xffff00, false);
	DrawCircle(GetCenterX(), GetCenterY(), circleSize + 5, 0xffffff, false);
}

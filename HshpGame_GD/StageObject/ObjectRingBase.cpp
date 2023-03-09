#include "ObjectRingBase.h"

ObjectRingBase::ObjectRingBase() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectRingBase::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectRingBase::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectRingBase::Update()
{
	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectRingBase::Draw(int scroll, int color)
{
	DrawCircle(static_cast<int>(GetCenterX()) - scroll , static_cast<int>(GetCenterY()), static_cast<int>(circleSize), color, true);
	DrawCircle(static_cast<int>(GetCenterX()) - scroll, static_cast<int>(GetCenterY()), static_cast<int>(circleSize) + 5, 0xffffff, false);
}

#include "ObjectDashRing.h"

ObjectDashRing::ObjectDashRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectDashRing::Init()
{
	m_IsExist = false;

	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectDashRing::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectDashRing::Update()
{
	if (!m_IsExist) return;

	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectDashRing::Draw()
{
	if (!m_IsExist) return;

	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY()), static_cast<int>(circleSize), 0xdc143c, true);
	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY()), static_cast<int>(circleSize) + 5, 0xffffff, false);
}

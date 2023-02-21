#include "ObjectRingBase.h"

ObjectRingBase::ObjectRingBase() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectRingBase::Init()
{
	m_IsExist = false;

	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectRingBase::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectRingBase::Update()
{
	if (!m_IsExist) return;

	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectRingBase::Draw(int color)
{
	if (!m_IsExist) return;

	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY()), static_cast<int>(circleSize), color, true);
	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY()), static_cast<int>(circleSize) + 5, 0xffffff, false);
}

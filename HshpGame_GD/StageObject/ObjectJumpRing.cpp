#include "ObjectJumpRing.h"

ObjectJumpRing::ObjectJumpRing() :
	circleSize(0.0f),
	sizeAcc(0.0f)
{
}

void ObjectJumpRing::Init()
{
	m_IsExist = false;

	m_pos.x = -Game::kBlockSize;
	m_pos.y = -Game::kBlockSize;

	circleSize = (Game::kBlockSize / 2) - 5.0f;
	sizeAcc = 0.5f;
}

void ObjectJumpRing::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectJumpRing::Update()
{
	if (!m_IsExist) return;

	circleSize += sizeAcc;

	if (circleSize > (Game::kBlockSize / 2) - 5) sizeAcc *= -1;
	else if (circleSize < (Game::kBlockSize / 2) - 10) sizeAcc *= -1;
}

void ObjectJumpRing::Draw()
{
	if (!m_IsExist) return;

	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY()), static_cast<int>(circleSize), 0xffff00, true);
	DrawCircle(static_cast<int>(GetCenterX()), static_cast<int>(GetCenterY()), static_cast<int>(circleSize) + 5, 0xffffff, false);
}

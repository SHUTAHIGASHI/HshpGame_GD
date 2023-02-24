#include "ObjectBlock.h"

ObjectBlock::ObjectBlock():
	m_hBlock(-1)
{
}

void ObjectBlock::Init(int hBlock)
{
	m_IsExist = false;

	m_pos.x = 0;
	m_pos.y = 0;

	m_hBlock = hBlock;
}

void ObjectBlock::SetPos(float X, float Y)
{
	m_IsExist = true;

	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectBlock::Update()
{
}

void ObjectBlock::Draw()
{
	if (!m_IsExist) return;

	int imgX, imgY, imgW, imgH;
	imgX = 1, imgY = 1, imgW = 14, imgH = 14;

	DrawRectExtendGraphF(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 
		imgX, imgY, imgW, imgH, m_hBlock, true);
}

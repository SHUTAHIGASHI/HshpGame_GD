#include "MapObject.h"

MapObject::MapObject() :
	m_pos()
{
}

void MapObject::Init()
{
	m_pos.x = Game::kScreenWidth - Game::kBlockSize;
	m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
}

void MapObject::Update()
{

}

void MapObject::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

#include "ObjectBlock.h"

ObjectBlock::ObjectBlock()
{
}

void ObjectBlock::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;
}

void ObjectBlock::SetPos()
{
	m_pos.x = Game::kScreenWidth - Game::kBlockSize;
	m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
}

void ObjectBlock::Update()
{
	m_pos.x += -Game::kMoveSpeed;

	if (m_pos.x + Game::kBlockSize <= 0) m_pos.x = Game::kScreenWidth + Game::kBlockSize;
}

void ObjectBlock::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
	//DrawTriangle(m_pos.x, m_pos.y, m_pos.x + Game::kBlockSize, m_pos.y + Game::kBlockSize, 0xFF0000, true);
}

bool ObjectBlock::CollisionCheck(float X, float Y)
{
	// 当たっていない場合処理をスキップ
	if (GetRight() <= X) return false;
	if (X + Game::kBlockSize <= GetLeft()) return false;
	if (GetBottom() <= Y) return false;
	if (Y + Game::kBlockSize <= GetTop()) return false;

	// 当たっている場合プレイヤーを死亡判定にする
	return true;
}

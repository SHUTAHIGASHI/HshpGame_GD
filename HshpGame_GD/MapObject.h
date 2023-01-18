#pragma once

#include "game.h"

enum class ObjectType
{
	Block,
	Spike,
	End
};

class MapObject
{
public:
	MapObject();
	~MapObject() {}

	void Init();

	void Update();

	void Draw();

	bool CollisionCheck(float X, float Y);

	// 当たり判定用に四方向の座標取得　
	float GetLeft()	const { return m_pos.x; }
	float GetRight()	const { return m_pos.x + Game::kBlockSize; }
	float GetTop()	const { return m_pos.y; }
	float GetBottom() const { return m_pos.y + Game::kBlockSize; }
private:

	// ブロック表示位置
	Vec2 m_pos;


};


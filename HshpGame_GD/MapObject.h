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
private:

	// ブロック表示位置
	Vec2 m_pos;


};


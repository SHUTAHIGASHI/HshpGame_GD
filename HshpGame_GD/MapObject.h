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

	// �u���b�N�\���ʒu
	Vec2 m_pos;


};


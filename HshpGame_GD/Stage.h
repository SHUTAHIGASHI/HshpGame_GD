#pragma once

#include "Game.h"
#include "MapObject.h"

namespace
{
	constexpr int kBlockMax = 22;
}

class Stage
{
public:
	Stage();
	~Stage(){}

	void Init();
	
	void Update();

	void Draw();

	//bool IsHit() { return isHit; }
private:
	//bool isHit;
	
	// ブロック座標
	Vec2 m_pos[kBlockMax];
	Vec2 m_vec;
	
	//int m_stage[40];

	MapObject m_Object;
};


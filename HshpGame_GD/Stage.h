#pragma once

#include "Game.h"
#include "ObjectBlock.h"

namespace
{

}

class Stage
{
public:
	Stage();
	~Stage(){}

	void Init();
	
	void Update();

	void Draw();

	bool CollisionCheck(Vec2 playerPos);

	void GetBlockPos(Vec2& blockPos){ blockPos = m_Object.GetPos(); }

	bool IsUnder(Vec2 playerPos);
private:
	//bool isHit;
	
	// ブロック座標
	Vec2 m_pos;
	Vec2 m_vec;
	
	int m_stage[Game::kScreenWidthNum][Game::kScreenHeightNum];

	ObjectBlock m_Object;
};


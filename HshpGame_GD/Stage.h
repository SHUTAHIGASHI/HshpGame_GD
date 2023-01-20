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

	bool IsUnder(Vec2 playerPos);
private:
	//bool isHit;

	ObjectBlock m_Object[Game::kScreenHeightNum][Game::kScreenWidthNum];
};


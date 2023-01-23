#pragma once

#include "Game.h"
#include "ObjectBlock.h"

class PlayerCube;

namespace
{

}

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void setPlayer(PlayerCube* cube) { pCube = cube; }

	void Init();
	
	void Update();

	void Draw();

	bool CollisionCheck(Vec2 playerPos, int H, int W);

	bool IsUnder(Vec2 playerPos, float &tempPos, int Y, int X);
private:
	//bool isHit;

	ObjectBlock m_Object[Game::kScreenHeightNum][Game::kScreenWidthNum];

	PlayerCube* pCube;
};


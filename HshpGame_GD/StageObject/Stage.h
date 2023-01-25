#pragma once

#include "Game.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"

class PlayerCube;

namespace
{

}

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void setPlayer(PlayerCube* cube) { m_pCube = cube; }

	void Init();
	
	void Update();

	void Draw();

	bool CollisionCheck(Vec2 playerPos, int H, int W, ObjectType &object);

	bool IsUnder(Vec2 playerPos, float &tempPos, int Y, int X);
private:
	ObjectBlock m_ObjectBlock[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectSpike m_ObjectSpike[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpRing m_ObjectJumpRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpPad m_ObjectJumpPad[Game::kScreenHeightNum][Game::kScreenWidthNum];

	PlayerCube* m_pCube;
};

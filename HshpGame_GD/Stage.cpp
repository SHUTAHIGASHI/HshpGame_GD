#include "Stage.h"
#include "game.h"
#include "playerCube.h"

namespace
{
	//マップデータ
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,3,0,0,0,0,0,0,0,0,0,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
}

Stage::Stage() :
	m_pCube(nullptr)
{

}

void Stage::Init()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			int blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;
			
			if (m_stage[i][j] == 2) m_ObjectBlock[i][j].Init(blockPosX, blockPosY);
			if (m_stage[i][j] == 3) m_ObjectJumpRing[i][j].Init(blockPosX, blockPosY);
			if (m_stage[i][j] == 4) m_ObjectJumpPad[i][j].Init(blockPosX, blockPosY);
		}
	}
}

void Stage::Update()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_ObjectBlock[i][j].Update();
			m_ObjectJumpRing[i][j].Update();
			m_ObjectJumpPad[i][j].Update();
		}
	}
}

void Stage::Draw()
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			int drawPosX = 0, drawPosY = 0;
			drawPosX = (j * Game::kBlockSize);
			drawPosY = (i * Game::kBlockSize);
			
			// デバック用白線
			//DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, 0xFFFFFF, false);

			if (m_stage[i][j] == 1)
			{
				int stageColor = 0x4169e1;
				DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, stageColor, true);

				stageColor = 0xffffff;
				DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, stageColor, false);
			}

			// ステージギミックの描画
			if (m_stage[i][j] == 2) m_ObjectBlock[i][j].Draw();
			if (m_stage[i][j] == 3) m_ObjectJumpRing[i][j].Draw();
			if (m_stage[i][j] == 4) m_ObjectJumpPad[i][j].Draw();
		}
	}
}

// プレイヤーとオブジェクトの当たり判定チェック
bool Stage::CollisionCheck(Vec2 playerPos, int H, int W, ObjectType &object)
{
	// 当たっている場合、trueを返す
	if (m_ObjectBlock[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectBlock[H][W].GetLeft() &&
		m_ObjectBlock[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectBlock[H][W].GetTop())
	{
		object = ObjectType::Block;
		return true;
	}

	if (m_ObjectJumpRing[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectJumpRing[H][W].GetLeft() &&
		m_ObjectJumpRing[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectJumpRing[H][W].GetTop())
	{
		object = ObjectType::JumpRing;
		return true;
	}

	if (m_ObjectJumpPad[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectJumpPad[H][W].GetLeft() &&
		m_ObjectJumpPad[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectJumpPad[H][W].GetTop() + Game::kBlockSize - (Game::kBlockSize / 4))
	{
		object = ObjectType::JumpPad;
		return true;
	}

	// 当たっていない場合、falseを返す
	return false;
}

// オブジェクトがプレイヤーの下にあるかどうか
bool Stage::IsUnder(Vec2 playerPos, float &tempPos,  int H, int W)
{	
	// ブロックが存在する場合
	if(m_stage[H][W] == 2)
	{
		// プレイヤーの中心、ブロックの上面での判定
		// 下にある場合、trueを返す
		if (m_ObjectBlock[H][W].GetPos().y > playerPos.y + (Game::kBlockSize / 2))
		{
			// ブロックの座標を代入
			tempPos = m_ObjectBlock[H][W].GetPos().y;
			return true;
		}
	}
	
	// 下ではない場合、falseを返す
	return false;
}

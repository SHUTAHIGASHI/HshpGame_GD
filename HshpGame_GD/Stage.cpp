#include "Stage.h"
#include "game.h"

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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0},

		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};
}

Stage::Stage()
{

}

void Stage::Init()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_Object[i][j].Init();

			int blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;
			
			if (m_stage[i][j] == 1)
			{
				m_Object[i][j].SetPos(blockPosX, blockPosY);
			}
		}
	}
}

void Stage::Update()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			//m_Object[i][j].Update();
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
			DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, 0xFFFFFF, false);

			if (m_stage[i][j] == 2)
			{
				int stageColor = 0x40e0d0;

				DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, stageColor, true);

				stageColor = 0x483d8b;

				DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, stageColor, false);
			
			}			
				
			if (m_stage[i][j] == 1)
			{
				// ステージギミックの描画
				m_Object[i][j].Draw();
			}
		}
	}
}

bool Stage::CollisionCheck(Vec2 playerPos)
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			// 当たっている場合プレイヤーを死亡判定にする
			if (m_Object[i][j].GetRight() >= playerPos.x &&
				playerPos.x + Game::kBlockSize >= m_Object[i][j].GetLeft() &&
				m_Object[i][j].GetBottom() >= playerPos.y &&
				playerPos.y + Game::kBlockSize >= m_Object[i][j].GetTop()) return true;
		}
	}

	// 当たっていない場合処理をスキップ
	return false;
}

bool Stage::IsUnder(Vec2 playerPos)
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			if(m_stage[i][j] == 1)
			{
				// プレイヤーの下面、ブロックの上面での判定
				if (playerPos.y + (Game::kBlockSize / 2) < m_Object[i][j].GetPos().y) return true;
			}
		}
	}

	return false;
}

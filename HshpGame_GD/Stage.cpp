#include "Stage.h"
#include "game.h"

Stage::Stage() :
	m_pos(),
	m_vec(),
	m_stage()
{

}

void Stage::Init()
{
	for (int i = 0; i < Game::kScreenWidthNum; i++)
	{
		for (int j = 0; j < Game::kScreenHeightNum; j++)
		{
			m_stage[i][j] = false;
		}
	}
	
	m_vec.x = -Game::kMoveSpeed;
	m_vec.y = 0.0f;
	
	m_pos.x = Game::kStageLowerLimit;
	m_pos.y = Game::kStageLowerLimit;
	
	
	m_Object.Init();
	m_Object.SetPos(Game::kScreenWidthHalf, Game::kStageLowerLimit - Game::kBlockSize);
}

void Stage::Update()
{	
	m_Object.Update();
}

void Stage::Draw()
{
	// ステージの線の表示
	DrawLine(0, Game::kStageUpperLimit, Game::kScreenWidth, Game::kStageUpperLimit, 0xffffff);

	int stageColor = 0x40e0d0;

	DrawBox(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit + Game::kBlockSize, stageColor, true);

	stageColor = 0xe0ffff;

	DrawLine(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit, stageColor, true);
	DrawLine(0, Game::kStageLowerLimit + Game::kBlockSize, Game::kScreenWidth, Game::kStageLowerLimit + Game::kBlockSize, stageColor, true);
	
	for (int i = 0; i < Game::kScreenWidthNum; i++)
	{
		for (int j = 0; j < Game::kScreenHeightNum; j++)
		{
			int drawPosX = 0, drawPosY = 0;
			drawPosX = (i * Game::kBlockSize);
			drawPosY = (j * Game::kBlockSize);

			DrawBox(drawPosX, drawPosY, drawPosX + Game::kBlockSize, drawPosY + Game::kBlockSize, stageColor, false);
		}
	}

	// ステージギミックの描画
	m_Object.Draw();
}

bool Stage::CollisionCheck(Vec2 playerPos)
{
	// 当たっていない場合処理をスキップ
	if (m_Object.GetRight() < playerPos.x) return false;
	if (playerPos.x + Game::kBlockSize < m_Object.GetLeft()) return false;
	if (m_Object.GetBottom() < playerPos.y) return false;
	if (playerPos.y + Game::kBlockSize < m_Object.GetTop()) return false;

	// 当たっている場合プレイヤーを死亡判定にする
	return true;
}

bool Stage::IsUnder(Vec2 playerPos)
{
	if (playerPos.y + (Game::kBlockSize / 2) < m_Object.GetCenterY()) return true;
	
	return false;
}

#include "Stage.h"
#include "game.h"

Stage::Stage() :
	m_pos(),
	m_vec()
{

}

void Stage::Init()
{
	m_vec.x = -10;
	
	for (int i = 0; i < kBlockMax; i++)
	{
		m_pos[i].x = 0;
		m_pos[i].y = 0;
	}

	m_Object.Init();
}

void Stage::Update()
{
	for (int i = 0; i < kBlockMax; i++)
	{
		m_pos[i] += m_vec;

		if (m_pos[i].x + Game::kBlockSize < 0.0f)
		{
			
		}
	}
	m_Object.Update();
}

void Stage::Draw()
{
	// ステージの線の表示
	DrawLine(0, Game::kStageUpperLimit, Game::kScreenWidth, Game::kStageUpperLimit, GetColor(255, 255, 255));
	//DrawLine(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit, GetColor(255, 255, 255));

	for (int i = 0; i < kBlockMax; i++)
	{
		if(i == 5) DrawBox(m_pos[i].x + (i * Game::kBlockSize), Game::kStageLowerLimit, m_pos[i].x + (i * Game::kBlockSize) + Game::kBlockSize, Game::kStageLowerLimit + Game::kBlockSize, 0xFF0000, false);
		else DrawBox(m_pos[i].x + (i * Game::kBlockSize), Game::kStageLowerLimit, m_pos[i].x + (i * Game::kBlockSize) + Game::kBlockSize, Game::kStageLowerLimit + Game::kBlockSize, 0xFFFFFF, false);
	}

	// ステージギミックの描画
	m_Object.Draw();
}

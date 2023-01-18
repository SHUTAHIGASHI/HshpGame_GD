#include "Stage.h"
#include "game.h"

Stage::Stage() :
	m_pos(),
	m_vec()
{

}

void Stage::Init()
{
	m_vec.x = -Game::kMoveSpeed;
	m_vec.y = 0.0f;
	
	for (int i = 0; i < kBlockMax; i++)
	{
		m_pos[i].x = i * Game::kBlockSize;
		m_pos[i].y = Game::kStageLowerLimit;
	}

	m_Object.Init();
}

void Stage::Update()
{	
	for (int i = 0; i < kBlockMax; i++)
	{
		m_pos[i] += m_vec;

		if (m_pos[i].x + Game::kBlockSize <= 0.0f)
		{
			float tempMaxX = 0.0f;
			for (int j = 0; j < kBlockMax; j++)
			{
				if (m_pos[j].x >= tempMaxX)
				{
					tempMaxX = m_pos[j].x;
				}
			}

			m_pos[i].x = tempMaxX + Game::kBlockSize;
			if (i == 0) m_pos[i].x -= Game::kMoveSpeed;
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
		int textColor = 0;
		if (i % 2 == 0) textColor = 0xFFFFFF;
		else textColor = 0xFF00FF;
		
		DrawBox(m_pos[i].x, m_pos[i].y, m_pos[i].x + Game::kBlockSize, m_pos[i].y+ Game::kBlockSize, textColor, false);
	}

	// ステージギミックの描画
	m_Object.Draw();
}

#include "playerCube.h"
#include "game.h"

PlayerCube::PlayerCube() :
	m_handle(-1),
	m_height(0),
	m_width(0),
	m_pos(),
	m_vec(),
	m_angle(0.0),
	m_isDead(false)
{
}

void PlayerCube::Init(int playerHandle)
{
	m_handle = playerHandle;
	GetGraphSizeF(m_handle, &m_width, &m_height);
	
	m_isDead = false;

	m_pos.x = Game::kScreenWidthHalf;
	m_pos.y = Game::kScreenHeightHalf;
}

void PlayerCube::Update()
{

}

void PlayerCube::Draw()
{
	DrawRotaGraph(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);
	DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);
}

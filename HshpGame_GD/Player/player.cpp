#include "game.h"
#include "player.h"

Player::Player():
	m_handle(-1),
	m_deathEffectHandle(-1),
	m_height(0),
	m_width(0),
	m_effectHeight(0),
	m_effectWidth(0),
	m_countFrame(0),
	m_angle(0.0f),
	m_isMoveRight(false),
	m_isRevGravity(false),
	m_isField(false),
	m_pos(),
	m_vec(),
	m_isStageClear(false),
	m_isDead(false)
{
}

void Player::Init()
{
}

void Player::SetHandle(int playerHandle)
{
}

void Player::Update()
{
}

void Player::Draw()
{
}

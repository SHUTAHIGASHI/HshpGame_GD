#include "playerCube.h"
#include "MapObject.h"
#include "game.h"

namespace
{
    // 移動速度
    constexpr float kMoveSpeed = 12.0f;

    // 画像の回転速度
    constexpr float kRotaSpeed = 0.2f;

    // 画像の表示位置
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;

    // ジャンプ力
    constexpr float kJumpAcc = -24.0f;

    // 重力
    constexpr float kGravity = 2.0f;
}

PlayerCube::PlayerCube() :
    pObject(nullptr)
{
}

void PlayerCube::Init(int playerHandle)
{
	m_handle = playerHandle;
	GetGraphSizeF(m_handle, &m_width, &m_height);
	
	m_isDead = false;

	m_pos.x = Game::kScreenWidthHalf - (m_width / 2);
	m_pos.y = Game::kScreenHeightHalf - (m_height / 2);
}

void PlayerCube::Update(const InputState& input)
{
    m_pos += m_vec;
    m_vec.y += kGravity;
    m_angle += kRotaSpeed;

    // 地面との当たり判定
    bool isField = false;

    if (m_pos.y > Game::kStageLowerLimit - m_height)
    {
        m_angle = 0;
        m_pos.y = Game::kStageLowerLimit - m_height;

        m_pos.y = static_cast<float>(Game::kStageLowerLimit - m_height);    // ステージの範囲より下には行かない
        isField = true;

    }

    if (input.IsPressed(InputType::space))
    {
        if (isField)
        {
            m_vec.y = kJumpAcc;	// ジャンプ開始
        }
    }

    m_isDead = pObject->CollisionCheck(m_pos.x, m_pos.y);
}

void PlayerCube::Draw()
{
	DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);
	//DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);
}

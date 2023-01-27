#include "PlayerShip.h"
#include "game.h"
#include "Stage.h"

namespace
{
    // 画像の回転速度
    constexpr float kRotaSpeed = 0.2f;

    // 画像の表示位置
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;

    // 基本のジャンプ力
    constexpr float kJumpAcc = -14.0f;
    // オブジェクト起動時のジャンプ力
    constexpr float kJumpRingJumpAcc = -16.0f;
    constexpr float kJumpPadJumpAcc = -20.0f;

    // 重力
    constexpr float kGravity = 1.15f;
}

PlayerShip::PlayerShip() :
    m_pStage(nullptr),
    m_updateFunc(&PlayerShip::NormalUpdate)
{
}

void PlayerShip::Init(int playerHandle)
{
    m_updateFunc = &PlayerShip::NormalUpdate;

    m_handle = playerHandle;
    GetGraphSizeF(m_handle, &m_width, &m_height);

    m_isStageClear = false;
    m_isDead = false;

    m_pos.x = 0;
    m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;

    m_vec.x = Game::kMoveSpeed;
    m_vec.y = 0;

    m_isMoveRight = true;
    m_isRevGravity = false;
}

void PlayerShip::Update(const InputState& input)
{
    (this->*m_updateFunc)(input);
}

void PlayerShip::OnHitObject(const InputState& input)
{
    ObjectType object;
    for (int i = 0; i < Game::kScreenHeightNum; i++)
    {
        for (int j = 0; j < Game::kScreenWidthNum; j++)
        {
            if (m_pStage->CollisionCheck(m_pos, i, j, object))
            {
                float tempPos = 0.0f;
                DrawFormatString(100, 150, 0xffffff, "%d", static_cast<int>(object));
                if (object == ObjectType::JumpRing)
                {
                    if (input.IsTriggered(InputType::jump))
                    {
                        m_vec.y = kJumpRingJumpAcc;	// ジャンプ開始
                        return;
                    }
                }
                else if (object == ObjectType::JumpPad)
                {
                    m_vec.y = kJumpPadJumpAcc;	// ジャンプ開始
                    return;
                }
                else if (object == ObjectType::Spike)
                {
                    m_isDead = true;
                    return;
                }
                else if (object == ObjectType::GravityRing)
                {
                    if (input.IsTriggered(InputType::jump))
                    {
                        if (!m_isRevGravity)
                        {
                            m_isRevGravity = true;	// 重力反転
                            m_updateFunc = &PlayerShip::RevGravityUpdate;
                        }
                        else
                        {
                            m_isRevGravity = false;
                            m_updateFunc = &PlayerShip::NormalUpdate;
                        }
                        return;
                    }
                }
                else if (object == ObjectType::GoalGate)
                {
                    m_isStageClear = true;
                    return;
                }
                else if (m_pStage->IsUnder(m_pos, i, j, tempPos) && object == ObjectType::Block)
                {
                    m_angle = 0.0f;
                    m_vec.y = 0.0f;
                    m_pos.y = tempPos;
                    m_isField = true;
                    return;
                }
                else
                {
                    m_isDead = true;
                    return;
                }
            }
        }
    }
}

void PlayerShip::Draw()
{
    DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);
    //DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);
}

void PlayerShip::NormalUpdate(const InputState& input)
{
    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += kGravity;
    if (m_isMoveRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    // 地面との当たり判定
    m_isField = false;

    if (m_pos.x < 0)
    {
        m_vec.x *= -1;
        m_isMoveRight = true;
    }
    else if (m_pos.x + Game::kBlockSize > Game::kScreenWidth)
    {
        m_vec.x *= -1;
        m_isMoveRight = false;
    }

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = kJumpAcc;	// ジャンプ開始
        }
    }

    if (m_isDead)
    {
        m_updateFunc = &PlayerShip::DeadUpdate;
    }
}

void PlayerShip::RevGravityUpdate(const InputState& input)
{
    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += -kGravity;
    if (m_isMoveRight) m_angle += -kRotaSpeed;
    else m_angle += kRotaSpeed;

    // 地面との当たり判定
    m_isField = false;

    if (m_pos.x < 0)
    {
        m_vec.x *= -1;
        m_isMoveRight = true;
    }
    else if (m_pos.x + Game::kBlockSize > Game::kScreenWidth)
    {
        m_vec.x *= -1;
        m_isMoveRight = false;
    }

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = -kJumpAcc;	// ジャンプ開始
        }
    }

    if (m_isDead)
    {
        m_updateFunc = &PlayerShip::DeadUpdate;
    }
}

void PlayerShip::DeadUpdate(const InputState& input)
{
    return;
}

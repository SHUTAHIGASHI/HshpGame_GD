#include "playerCube.h"
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
    // 重力反転時の加速度
    constexpr float kRevGravityAcc = 2.0f;
    // 落下の最大速度
    constexpr float kGravityMax = 20.0f;
}

PlayerCube::PlayerCube() :
    m_pStage(nullptr),
    m_updateFunc(&PlayerCube::NormalUpdate)
{
}

void PlayerCube::Init(int playerHandle, int playerDeathEffect)
{
    if (m_pStage->GetStageState() == StageState::thirdStage)
    {
        m_updateFunc = &PlayerCube::StageScrollUpdate;
    }
    else
    {
        m_updateFunc = &PlayerCube::NormalUpdate;
    }
    m_handle = playerHandle;
    m_deathEffectHandle = playerDeathEffect;
    m_countFrame = 0;

	GetGraphSizeF(m_handle, &m_width, &m_height);
    GetGraphSizeF(m_deathEffectHandle, &m_effectWidth, &m_effectHeight);
	
    m_vec.x = Game::kMoveSpeed;
    m_vec.y = 0;

    if (m_pStage->GetStageState() == StageState::firstStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::secondStage)
    {
        m_pos.x = Game::kScreenWidth - Game::kBlockSize;
        m_pos.y = Game::kStageUpperLimit - Game::kBlockSize;
        m_isRotaRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::thirdStage)
    {
        m_pos.x = Game::kScreenWidthHalf - (Game::kBlockSize / 2);
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_vec.x = 0;
        m_isRotaRight = true;
    }
    else
    {
        m_pos.x = 0;
        m_pos.y = 0;
    }

    m_isStageClear = false;
	m_isDead = false;
    m_isRevGravity = false;
}

void PlayerCube::Update(const InputState& input)
{
    (this->*m_updateFunc)(input);
}

void PlayerCube::OnHitObject(const InputState& input)
{
    ObjectType object;
    for (int i = 0; i < Game::kScreenHeightNum; i++)
    {
        for (int j = 0; j < Game::kScreenWidthTripleNum; j++)
        {
            if (m_pStage->CollisionCheck(m_pos, i, j, object))
            {
                float tempPos = 0.0f;
                DrawFormatString(100, 150, 0xffffff, "%d", static_cast<int>(object));
                if (object == ObjectType::JumpRing)
                {
                    if (input.IsTriggered(InputType::jump))
                    {
                        if (!m_isRevGravity) m_vec.y = kJumpRingJumpAcc;	// ジャンプ開始
                        else m_vec.y = -kJumpRingJumpAcc;
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
                            m_vec.y = -kRevGravityAcc;
                            m_updateFunc = &PlayerCube::RevGravityUpdate;
                        }
                        else
                        {
                            m_isRevGravity = false; // 重力正常
                            m_vec.y = kRevGravityAcc;
                            m_updateFunc = &PlayerCube::NormalUpdate;
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

void PlayerCube::Draw()
{
    float effectW = 0.0f, effectH = 0.0f;
    effectW = static_cast<float>(m_effectWidth / 4);
    effectH = m_effectHeight;

    int effectX = 0, effectY = 0;
    effectX = static_cast<int>(m_countFrame / 4 * effectW);
    
    int effectScale = 20;
    
    if (m_isDead)
    {
        DrawRectExtendGraphF(GetLeft() - effectScale, GetTop() - effectScale, 
            GetRight() + effectScale, GetBottom() + effectScale, 
            effectX, effectY, 
            static_cast<int>(effectW), static_cast<int>(effectH),
            m_deathEffectHandle, true);
        m_countFrame++;
    }
    else if(!m_isDead) DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);

	//DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);
    //DrawFormatString(0, 50, 0xffffff, "%f", m_pos.x + Game::kBlockSize);
}

void PlayerCube::SetPlayerVec(int scroll)
{
    if(scroll == 0) m_vec.x = -Game::kMoveSpeed;
    else m_vec.x = Game::kMoveSpeed;
}

void PlayerCube::NormalUpdate(const InputState& input)
{
    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += kGravity;
    if (m_isRotaRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    if (m_vec.y > kGravityMax)
    {
        m_vec.y = kGravityMax;
    }

    // 地面との当たり判定
    m_isField = false;

    if (m_pos.x < 0)
    {
        m_vec.x *= -1;
        m_isRotaRight = true;
    }
    else if (m_pos.x + Game::kBlockSize > Game::kScreenWidth)
    {
        m_vec.x *= -1;
        m_isRotaRight = false;
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

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
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::RevGravityUpdate(const InputState& input)
{
    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += -kGravity;
    if (m_isRotaRight) m_angle += -kRotaSpeed;
    else m_angle += kRotaSpeed;

    if (m_vec.y < -kGravityMax)
    {
        m_vec.y = -kGravityMax;
    }

    // 地面との当たり判定
    m_isField = false;

    if (m_pos.x < 0)
    {
        m_vec.x *= -1;
        m_isRotaRight = true;
    }
    else if (m_pos.x + Game::kBlockSize > Game::kScreenWidth)
    {
        m_vec.x *= -1;
        m_isRotaRight = false;
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

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
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::StageScrollUpdate(const InputState& input)
{
    if (m_pos.x + Game::kBlockSize > Game::kScreenWidth)
    {
        m_isRotaRight = false;
        m_vec.x *= -1;
    }
    else if (m_pos.x < 0)
    {
        m_isRotaRight = true;
        m_vec.x *= -1;
    }

    // プレイヤーの挙動の処理
    m_vec.y += kGravity;
    m_pos += m_vec;
    if(m_isRotaRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    if (m_vec.y > kGravityMax)
    {
        m_vec.y = kGravityMax;
    }

    // 地面との当たり判定
    m_isField = false;

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

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
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::DeadUpdate(const InputState& input)
{
    return;
}

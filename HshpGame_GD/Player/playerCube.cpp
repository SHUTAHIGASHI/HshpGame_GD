#include "playerCube.h"
#include "game.h"
#include "Stage.h"

#include <cassert>

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
    constexpr float kMaxSpeed = 20.0f;
}

PlayerCube::PlayerCube() :
    m_playerState(PlayerState::Cube),
    m_pStage(nullptr),
    m_updateFunc(&PlayerCube::CubeNormalUpdate)
{
}

void PlayerCube::Init(int playerHandle, int playerDeathEffect)
{    
    m_handle = playerHandle;
    m_deathEffectHandle = playerDeathEffect;
    m_countFrame = 0;

	GetGraphSizeF(m_handle, &m_width, &m_height);
    GetGraphSizeF(m_deathEffectHandle, &m_effectWidth, &m_effectHeight);
	
    SetPlayerInfo();
}

void PlayerCube::SetPlayerInfo()
{
    ChangeUpdateType();
    SetSpawnPos();

    m_vec.x = Game::kMoveSpeed;
    m_vec.y = 0.0f;

    if (m_pStage->GetStageState() == StageState::fourthStage || m_pStage->GetStageState() == StageState::fifthStage
        || m_pStage->GetStageState() == StageState::seventhStage || m_pStage->GetStageState() == StageState::tenthStage)
    {
        m_vec.x = 0.0f;
        m_isScroll = true;
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

    int widthNum = 0;
    if(m_isScroll) widthNum = Game::kScreenWidthTripleNum;
    else widthNum = Game::kScreenWidthNum;

    for (int i = 0; i < Game::kScreenHeightNum; i++)
    {
        for (int j = 0; j < widthNum; j++)
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
                            m_updateFunc = &PlayerCube::CubeRevGravityUpdate;
                        }
                        else
                        {
                            m_isRevGravity = false; // 重力正常
                            m_vec.y = kRevGravityAcc;
                            m_updateFunc = &PlayerCube::CubeNormalUpdate;
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
    DrawFormatString(0, 50, 0xffffff, "%f", m_vec.x);
}

void PlayerCube::ChangeUpdateType()
{
    if (m_pStage->GetStageState() == StageState::fifthStage)
    {
        m_updateFunc = &PlayerCube::ShipNormalUpdate;
        m_playerState = PlayerState::Ship;
    }
    else
    {
        m_updateFunc = &PlayerCube::CubeNormalUpdate;
        m_playerState = PlayerState::Cube;
    }
}

void PlayerCube::SetSpawnPos()
{
    if (m_pStage->GetStageState() == StageState::firstStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kBlockSize * 5;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::secondStage)
    {
        m_pos.x = Game::kScreenWidth - Game::kBlockSize;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isRotaRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::thirdStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::fourthStage)
    {
        m_pos.x = Game::kScreenWidthHalf - (Game::kBlockSize / 2);
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::fifthStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kScreenHeightHalf;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::sixthStage)
    {
        m_pos.x = 0;
        m_pos.y = 0;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::seventhStage)
    {
        m_pos.x = 0;
        m_pos.y = 0;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::eighthStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isRotaRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::ninthStage)
    {
        m_pos.x = Game::kScreenWidth - Game::kBlockSize;
        m_pos.y = Game::kStageUpperLimit - Game::kBlockSize;
        m_isRotaRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::tenthStage)
    {
        m_pos.x = 0;
        m_pos.y = 0;
        m_isRotaRight = true;
    }
    else
    {
        m_pos.x = 0;
        m_pos.y = 0;
    }
}

void PlayerCube::SetPlayerVec(int scroll)
{
    if(scroll == 0) m_vec.x = -Game::kMoveSpeed;
    else m_vec.x = Game::kMoveSpeed;
}

void PlayerCube::CubeNormalUpdate(const InputState& input)
{
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

    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += kGravity;
    if (m_isRotaRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    if (m_vec.y > kMaxSpeed)
    {
        m_vec.y = kMaxSpeed;
    }

    // 地面との当たり判定
    m_isField = false;

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = kJumpAcc;	// ジャンプ開始
        }
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

    if (m_isDead)
    {
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::CubeRevGravityUpdate(const InputState& input)
{
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

    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += -kGravity;
    if (m_isRotaRight) m_angle += -kRotaSpeed;
    else m_angle += kRotaSpeed;

    if (m_vec.y < -kMaxSpeed)
    {
        m_vec.y = -kMaxSpeed;
    }

    // 地面との当たり判定
    m_isField = false;

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = -kJumpAcc;	// ジャンプ開始
        }
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

    if (m_isDead)
    {
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::ShipNormalUpdate(const InputState& input)
{
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

    if (input.IsPressed(InputType::jump))
    {
        m_vec.y += -kGravity;
    }
    else m_vec.y += kGravity;

    // プレイヤーの挙動の処理
    m_pos += m_vec;
    if (m_isRotaRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    if (m_vec.y < -kMaxSpeed)
    {
        m_vec.y = -kMaxSpeed;
    }
    else if (m_vec.y > kMaxSpeed)
    {
        m_vec.y = kMaxSpeed;
    }

    OnHitObject(input);

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

    if (m_isDead)
    {
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::ShipRevGravityUpdate(const InputState& input)
{
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

    if (input.IsPressed(InputType::jump))
    {
        m_vec.y += -kGravity;
    }
    else m_vec.y += kGravity;

    // プレイヤーの挙動の処理
    m_pos += m_vec;
    if (m_isRotaRight) m_angle += -kRotaSpeed;
    else m_angle += kRotaSpeed;

    if (m_vec.y < -kMaxSpeed)
    {
        m_vec.y = -kMaxSpeed;
    }
    else if (m_vec.y > kMaxSpeed)
    {
        m_vec.y = kMaxSpeed;
    }

    OnHitObject(input);

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

    if (m_isDead)
    {
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::DeadUpdate(const InputState& input)
{
    return;
}

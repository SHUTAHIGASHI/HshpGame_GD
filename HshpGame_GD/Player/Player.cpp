#include "Player.h"
#include "game.h"
#include "Stage.h"
#include "EffectRing.h"
#include <cassert>

namespace
{
    // 画像の回転速度
    constexpr float kRotaSpeed = 0.2f;
    constexpr float kShipRotaSpeed = 0.06f;

    // 画像の表示位置
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;

    constexpr float kPlayerInitPos = 0 - Game::kBlockSize;

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
    constexpr float kCubeMaxSpeed = 20.0f;
    constexpr float kWaveSpeed = 12.0f;
}

void Player::Init(int playerHandle, int playerDeathEffect, int hDeathSound)
{    
    m_pEffectRing = std::make_shared<EffectRing>();
    m_pEffectRing->Init();

    m_isStageClear = false;
    m_isDead = false;
    m_isRevGravity = false;
    m_isDashRingEnabled = false;
    m_isScroll = false;

    m_hPlayer = playerHandle;
    m_hDeathEffect = playerDeathEffect;
    m_deathCountFrame = 0;
    GetGraphSizeF(m_hDeathEffect, &m_effectWidth, &m_effectHeight);

    m_hDeathSound = hDeathSound;

    m_playerScale = 1.0;
	
    m_countFrame = 0;
    m_vec.x = Game::kMoveSpeed;
    m_vec.y = 0.0f;
    m_angle = 0;

    if (m_pStage->GetStageState() == StageState::fourthStage || m_pStage->GetStageState() == StageState::fifthStage
        || m_pStage->GetStageState() == StageState::seventhStage || m_pStage->GetStageState() == StageState::tenthStage)
    {
        m_vec.x = 0.0f;
        m_isScroll = true;
    }

    for (int i = 0; i < 5; i++)
    {
        m_lastPos[i].x = kPlayerInitPos;
        m_lastPos[i].y = kPlayerInitPos;
        m_lastAngle[i] = 0.0f;
    }

    ChangeUpdateType();
    SetSpawnPos();
}

void Player::End()
{
}

void Player::SetSpawnPos()
{
    if (m_pStage->GetStageState() == StageState::firstStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kBlockSize * 6;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::secondStage)
    {
        m_pos.x = Game::kScreenWidth - Game::kBlockSize;
        m_pos.y = Game::kStageLowerLimit;
        m_vec.x = -Game::kMoveSpeed;
        m_isMoveRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::thirdStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageLowerLimit;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::fourthStage)
    {
        m_pos.x = Game::kScreenWidthHalf - (Game::kBlockSize / 2);
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::fifthStage)
    {
        m_pos.x = Game::kScreenWidthHalf - (Game::kBlockSize / 2);
        m_pos.y = Game::kStageLowerLimit;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::sixthStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::seventhStage)
    {
        m_pos.x = Game::kScreenWidthHalf - (Game::kBlockSize / 2);
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::eighthStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageUpperLimit - (Game::kBlockSize * 3);
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::ninthStage)
    {
        m_pos.x = Game::kScreenWidth - (Game::kBlockSize * 2);
        m_pos.y = Game::kStageUpperLimit - Game::kBlockSize;
        m_vec.x = -Game::kMoveSpeed;
        m_isMoveRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::tenthStage)
    {
        m_pos.x = Game::kScreenWidthHalf - (Game::kBlockSize / 2);
        m_pos.y = Game::kBlockSize * 9;
        m_vec.x = -Game::kMoveSpeed;
        m_isMoveRight = false;
    }
    else
    {
        m_pos.x = 0;
        m_pos.y = Game::kBlockSize * 5;
        m_isMoveRight = true;
    }
}

void Player::ChangeUpdateType()
{
    if (m_pStage->GetStageState() == StageState::eighthStage)
    {
        m_updateFunc = &Player::CubeRevGravityUpdate;
        m_isRevGravity = true;
    }
    else
    {
        m_updateFunc = &Player::CubeNormalUpdate;
    }
}

void Player::Update(const InputState& input)
{
#ifdef _DEBUG
    if (input.IsTriggered(InputType::right)) m_isStageClear = true;
#endif
    if (m_isDead) return;

    m_pEffectRing->Update();

    (this->*m_updateFunc)(input);
}

void Player::OnHitObject(const InputState& input)
{
    ObjectType object;
    float tempPos = 0.0f;

    while(m_pStage->CollisionCheck(m_pos, object))
    {
        if (object == ObjectType::GoalGate)
        {
            m_updateFunc = &Player::GoalUpdate;
            return;
        }
        
        if (object == ObjectType::JumpRing)
        {
            if (input.IsTriggered(InputType::jump))
            {
                m_pEffectRing->SetEffect();
                m_isDashRingEnabled = false;
                if (!m_isRevGravity) m_vec.y = kJumpRingJumpAcc;	// ジャンプ開始
                else m_vec.y = -kJumpRingJumpAcc;
            }
            return;
        }
        
        if (object == ObjectType::JumpPad)
        {
            m_isDashRingEnabled = false;
            m_vec.y = kJumpPadJumpAcc;	// ジャンプ開始
            return;
        }
        
        if (object == ObjectType::Spike)
        {
            OnDead();
            return;
        }
        
        if (object == ObjectType::GravityRing)
        {
            if (input.IsTriggered(InputType::jump))
            {
                m_pEffectRing->SetEffect();
                m_isDashRingEnabled = false;
                if (!m_isRevGravity)
                {
                    m_isRevGravity = true;	// 重力反転
                    m_vec.y = -kRevGravityAcc;
                    m_updateFunc = &Player::CubeRevGravityUpdate;
                }
                else
                {
                    m_isRevGravity = false; // 重力正常
                    m_vec.y = kRevGravityAcc;
                    m_updateFunc = &Player::CubeNormalUpdate;
                }
            }
            return;
        }
        
        if (object == ObjectType::DashRing)
        {
            if (input.IsTriggered(InputType::jump))
            {
                m_pEffectRing->SetEffect();
                m_vec.y = 0.0f;
                m_isDashRingEnabled = true;
            }
            return;
        }
        
        if (object == ObjectType::ReverseRing)
        {
            if (input.IsTriggered(InputType::jump))
            {
                m_pEffectRing->SetEffect();
                m_vec.x *= -1;
                if (m_isMoveRight) m_isMoveRight = false;
                else m_isMoveRight = true;
                m_pStage->ChangeScroll();
            }
            return;
        }
        
        if (object == ObjectType::Block)
        {
            m_isDashRingEnabled = false;
            if (!m_isRevGravity)
            {
                if (m_pStage->IsUnder(tempPos))
                {
                    m_isField = true;
                    m_vec.y = 0.0f;
                    m_angle = 0.0f;
                    m_pos.y = tempPos;
                }
                else
                {
                    OnDead();
                    return;
                }
            }
            else if (m_isRevGravity)
            {
                if (m_pStage->IsTop(tempPos))
                {
                    m_isField = true;
                    m_vec.y = 0.0f;
                    m_angle = 0.0f;
                    m_pos.y = tempPos;
                }
                else
                {
                    OnDead();
                    return;
                }
            }
        }
    }
}

void Player::OnDead()
{
    m_pEffectRing->End();

    m_isDead = true;
    PlaySoundMem(m_hDeathSound, DX_PLAYTYPE_BACK);
}

void Player::Draw()
{
    float effectW = 0.0f, effectH = 0.0f;
    effectW = static_cast<float>(m_effectWidth / 4);
    effectH = m_effectHeight;

    int effectX = 0, effectY = 0;
    effectX = static_cast<int>(m_deathCountFrame / 4 * effectW);
    
    int effectScale = 20;
    
    if (m_isDead)
    {
        DrawRectExtendGraphF(m_pos.x - effectScale, m_pos.y - effectScale, 
            (m_pos.x + Game::kBlockSize) + effectScale, (m_pos.y + Game::kBlockSize) + effectScale,
            effectX, effectY, 
            static_cast<int>(effectW), static_cast<int>(effectH),
            m_hDeathEffect, true);
        m_deathCountFrame++;
    }
    else if (!m_isDead)
    {
        DrawMoveEffect();
        
        float drawPosX = 0.0f, drawPosY = 0.0f;
        int imgX = 0, imgY = 0, imgW = 0, imgH = 0;

        drawPosX = GetCenterX(), drawPosY = GetCenterY();
        imgW = Game::kBlockSize, imgH = Game::kBlockSize;

        DrawRectRotaGraphF(drawPosX, drawPosY, imgX, imgY, imgW, imgH, m_playerScale, m_angle, m_hPlayer, true, !m_isMoveRight);
    }

    m_pEffectRing->Draw(m_pos);
	//DrawBox(GetLeft(), GetTop(), GetRight(), GetBottom(), GetColor(255, 255, 255), false);
}

void Player::DrawMoveEffect()
{
    float drawPosX = 0.0f, drawPosY = 0.0f;
    int imgX = 0, imgY = 0, imgW = 0, imgH = 0;
    
    for (int i = 0; i < 5; i++)
    {
        if (!m_isScroll)
        {
            drawPosX = m_lastPos[i].x + (Game::kBlockSize / 2);
            drawPosY = m_lastPos[i].y + (Game::kBlockSize / 2);
            imgW = Game::kBlockSize, imgH = Game::kBlockSize;
        }
        else
        {
            if (m_isMoveRight) drawPosX = (m_lastPos[i].x + (Game::kBlockSize / 2)) - (Game::kMoveSpeed * i);
            else drawPosX = (m_lastPos[i].x + (Game::kBlockSize / 2)) + (Game::kMoveSpeed * i);
            drawPosY = m_lastPos[i].y + (Game::kBlockSize / 2);
            imgW = Game::kBlockSize, imgH = Game::kBlockSize;
        }

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 40);
        DrawRectRotaGraphF(drawPosX, drawPosY, imgX, imgY, imgW, imgH, 1, m_lastAngle[i], m_hPlayer, true, !m_isMoveRight);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Player::SetPlayerVec(int scroll)
{
    if(scroll == 0) m_vec.x = -Game::kMoveSpeed;
    else m_vec.x = Game::kMoveSpeed;
}

void Player::CubeNormalUpdate(const InputState& input)
{
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

    // プレイヤーの挙動の処理
    m_pos += m_vec;
    if(!m_isDashRingEnabled) m_vec.y += kGravity;
    if (m_isMoveRight && !m_isField) m_angle += kRotaSpeed;
    else if(!m_isMoveRight && !m_isField) m_angle += -kRotaSpeed;

    if (m_vec.y > kCubeMaxSpeed)
    {
        m_vec.y = kCubeMaxSpeed;
    }

    // 地面との当たり判定
    m_isField = false;

    if (input.IsTriggered(InputType::jump)) m_isDashRingEnabled = false;

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = kJumpAcc;	// ジャンプ開始
        }
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight)
    {
        OnDead();
    }

    m_lastPos[m_countFrame] = m_pos;
    m_lastAngle[m_countFrame] = m_angle;
    m_countFrame++;
    if (m_countFrame > 4) m_countFrame = 0;
}

void Player::CubeRevGravityUpdate(const InputState& input)
{
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

    // プレイヤーの挙動の処理
    m_pos += m_vec;
    if (!m_isDashRingEnabled) m_vec.y += -kGravity;
    if (m_isMoveRight && !m_isField) m_angle += -kRotaSpeed;
    else if(!m_isMoveRight && !m_isField)m_angle += kRotaSpeed;

    if (m_vec.y < -kCubeMaxSpeed)
    {
        m_vec.y = -kCubeMaxSpeed;
    }

    // 地面との当たり判定
    m_isField = false;

    if (input.IsTriggered(InputType::jump)) m_isDashRingEnabled = false;

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = -kJumpAcc;	// ジャンプ開始
        }
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight)
    {
        OnDead();
    }

    m_lastPos[m_countFrame] = m_pos;
    m_lastAngle[m_countFrame] = m_angle;
    m_countFrame++;
    if (m_countFrame > 4) m_countFrame = 0;
}

void Player::GoalUpdate(const InputState& input)
{
    m_playerScale -= 0.05;
    if (m_playerScale < 0) 
        
    m_isStageClear = true;

    return;
}

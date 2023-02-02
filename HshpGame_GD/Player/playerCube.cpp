#include "Player.h"
#include "game.h"
#include "Stage.h"
#include <cassert>

namespace
{
    // �摜�̉�]���x
    constexpr float kRotaSpeed = 0.2f;
    constexpr float kShipRotaSpeed = 0.06f;

    // �摜�̕\���ʒu
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;

    // ��{�̃W�����v��
    constexpr float kJumpAcc = -14.0f;
    // �I�u�W�F�N�g�N�����̃W�����v��
    constexpr float kJumpRingJumpAcc = -16.0f;
    constexpr float kJumpPadJumpAcc = -20.0f;

    // �d��
    constexpr float kGravity = 1.15f;
    // �d�͔��]���̉����x
    constexpr float kRevGravityAcc = 2.0f;
    // �����̍ő呬�x
    constexpr float kMaxSpeed = 20.0f;
}

void Player::Init(int playerHandle, int playerDeathEffect)
{    
    m_playerHandle = playerHandle;
    m_deathEffectHandle = playerDeathEffect;
    m_countFrame = 0;

    GetGraphSizeF(m_deathEffectHandle, &m_effectWidth, &m_effectHeight);
	
    SetStartInfo();
}

void Player::SetStartInfo()
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

    if (m_playerState == PlayerState::Ship) m_angle = 0;

    m_isStageClear = false;
    m_isDead = false;
    m_isRevGravity = false;
}

void Player::Update(const InputState& input)
{
    (this->*m_updateFunc)(input);
}

void Player::OnHitObject(const InputState& input)
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
                        if (!m_isRevGravity) m_vec.y = kJumpRingJumpAcc;	// �W�����v�J�n
                        else m_vec.y = -kJumpRingJumpAcc;
                        return;
                    }
                }
                else if (object == ObjectType::JumpPad)
                {
                    m_vec.y = kJumpPadJumpAcc;	// �W�����v�J�n
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
                            m_isRevGravity = true;	// �d�͔��]
                            m_vec.y = -kRevGravityAcc;
                            m_updateFunc = &Player::CubeRevGravityUpdate;
                        }
                        else
                        {
                            m_isRevGravity = false; // �d�͐���
                            m_vec.y = kRevGravityAcc;
                            m_updateFunc = &Player::CubeNormalUpdate;
                        }
                        return;
                    }
                }
                else if (object == ObjectType::GoalGate)
                {
                    m_isStageClear = true;
                    return;
                }
                else if (object == ObjectType::Block)
                {
                    if (!m_isRevGravity || m_playerState == PlayerState::Ship)
                    {
                        if (m_pStage->IsUnder(m_pos, i, j, tempPos))
                        {
                            m_angle = 0.0f;
                            m_vec.y = 0.0f;
                            m_pos.y = tempPos;
                            m_isField = true;
                            continue;
                        }
                    }
                    if (m_isRevGravity || m_playerState == PlayerState::Ship)
                    {
                        if (m_pStage->IsTop(m_pos, i, j, tempPos))
                        {
                            m_angle = 0.0f;
                            m_vec.y = 0.0f;
                            m_pos.y = tempPos;
                            m_isField = true;
                            continue;
                        }
                    }

                    m_isDead = true;
                    return;
                }
            }
        }
    }
}

void Player::Draw()
{
    float effectW = 0.0f, effectH = 0.0f;
    effectW = static_cast<float>(m_effectWidth / 4);
    effectH = m_effectHeight;

    int effectX = 0, effectY = 0;
    effectX = static_cast<int>(m_countFrame / 4 * effectW);
    
    int effectScale = 20;
    
    if (m_isDead)
    {
        DrawRectExtendGraphF(m_pos.x - effectScale, m_pos.y - effectScale, 
            (m_pos.x + Game::kBlockSize) + effectScale, (m_pos.y + Game::kBlockSize) + effectScale,
            effectX, effectY, 
            static_cast<int>(effectW), static_cast<int>(effectH),
            m_deathEffectHandle, true);
        m_countFrame++;
    }
    else if (!m_isDead)
    {
        float drawPosX = 0.0f, drawPosY = 0.0f;
        int imgX = 0, imgY = 0, imgW = 0, imgH = 0;
        if (m_playerState == PlayerState::Cube)
        {
            drawPosX = GetCubeCenterX(), drawPosY = GetCenterY();
            imgW = Game::kBlockSize, imgH = Game::kBlockSize;
        }
        else if (m_playerState == PlayerState::Ship)
        {
            drawPosX = GetShipCenterX(), drawPosY = GetCenterY();
            imgX = Game::kBlockSize, imgW = Game::kShipWidth, imgH = Game::kBlockSize;
        }

        DrawRectRotaGraphF(drawPosX, drawPosY, imgX, imgY, imgW, imgH, 1, m_angle, m_playerHandle, true, !m_isMoveRight);
    }
	//DrawBox(GetLeft(), GetTop(), GetRight(), GetBottom(), GetColor(255, 255, 255), false);
    //DrawFormatString(0, 50, 0xffffff, "%f", m_vec.x);
}

void Player::ChangeUpdateType()
{
    if (m_pStage->GetStageState() == StageState::fifthStage)
    {
        m_updateFunc = &Player::ShipUpdate;
        m_playerState = PlayerState::Ship;
    }
    else
    {
        m_updateFunc = &Player::CubeNormalUpdate;
        m_playerState = PlayerState::Cube;
    }
}

void Player::SetSpawnPos()
{
    if (m_pStage->GetStageState() == StageState::firstStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kBlockSize * 5;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::secondStage)
    {
        m_pos.x = Game::kScreenWidth - Game::kBlockSize;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isMoveRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::thirdStage)
    {
        m_pos.x = 0;
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;;
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
        m_pos.x = Game::kScreenWidthHalf;
        m_pos.y = Game::kScreenHeightHalf;
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
        m_pos.y = Game::kStageLowerLimit - Game::kBlockSize;
        m_isMoveRight = true;
    }
    else if (m_pStage->GetStageState() == StageState::ninthStage)
    {
        m_pos.x = Game::kScreenWidth - Game::kBlockSize;
        m_pos.y = Game::kStageUpperLimit - Game::kBlockSize;
        m_isMoveRight = false;
    }
    else if (m_pStage->GetStageState() == StageState::tenthStage)
    {
        m_pos.x = 0;
        m_pos.y = 0;
        m_isMoveRight = true;
    }
    else
    {
        m_pos.x = 0;
        m_pos.y = 0;
    }
}

void Player::SetPlayerVec(int scroll)
{
    if(scroll == 0) m_vec.x = -Game::kMoveSpeed;
    else m_vec.x = Game::kMoveSpeed;
}

float Player::GetRight() const
{
    if (m_playerState == PlayerState::Cube)
    {
        return (m_pos.x + Game::kBlockSize);
    }
    else if (m_playerState == PlayerState::Ship)
    {
        return (m_pos.x + Game::kShipWidth);
    }
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

    // �v���C���[�̋����̏���
    m_pos += m_vec;
    m_vec.y += kGravity;
    if (m_isMoveRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    if (m_vec.y > kMaxSpeed)
    {
        m_vec.y = kMaxSpeed;
    }

    // �n�ʂƂ̓����蔻��
    m_isField = false;

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = kJumpAcc;	// �W�����v�J�n
        }
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

    if (m_isDead)
    {
        m_updateFunc = &Player::DeadUpdate;
    }
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

    // �v���C���[�̋����̏���
    m_pos += m_vec;
    m_vec.y += -kGravity;
    if (m_isMoveRight) m_angle += -kRotaSpeed;
    else m_angle += kRotaSpeed;

    if (m_vec.y < -kMaxSpeed)
    {
        m_vec.y = -kMaxSpeed;
    }

    // �n�ʂƂ̓����蔻��
    m_isField = false;

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (m_isField)
        {
            m_vec.y = -kJumpAcc;	// �W�����v�J�n
        }
    }

    if (m_pos.y + Game::kBlockSize < 0 || m_pos.y > Game::kScreenHeight) m_isDead = true;

    if (m_isDead)
    {
        m_updateFunc = &Player::DeadUpdate;
    }
}

void Player::ShipUpdate(const InputState& input)
{
    if (m_pos.x < 0)
    {
        m_vec.x *= -1;
        m_angle *= -1;
        m_isMoveRight = true;
    }
    else if (m_pos.x + Game::kBlockSize > Game::kScreenWidth)
    {
        m_vec.x *= -1;
        m_angle *= -1;
        m_isMoveRight = false;
    }

    if (input.IsPressed(InputType::jump))
    {
        m_vec.y += -kGravity;
        if(m_isMoveRight) m_angle += -kShipRotaSpeed;
        else m_angle += kShipRotaSpeed;
    }
    else
    {
        m_vec.y += kGravity;
        if (m_isMoveRight) m_angle += kShipRotaSpeed;
        else m_angle += -kShipRotaSpeed;
    }

    if (m_angle > 1) m_angle = 1;
    else if (m_angle < -1) m_angle = -1;

    // �v���C���[�̋����̏���
    m_pos += m_vec;

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
        m_updateFunc = &Player::DeadUpdate;
    }
}

void Player::DeadUpdate(const InputState& input)
{
    return;
}

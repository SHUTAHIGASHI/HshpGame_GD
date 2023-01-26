#include "playerCube.h"
#include "game.h"
#include "Stage.h"

namespace
{
    // �摜�̉�]���x
    constexpr float kRotaSpeed = 0.2f;

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
}

PlayerCube::PlayerCube() :
    m_pStage(nullptr),
    m_updateFunc(&PlayerCube::NormalUpdate)
{
}

void PlayerCube::Init(int playerHandle)
{
    m_updateFunc = &PlayerCube::NormalUpdate;
    
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

void PlayerCube::Update(const InputState& input)
{
    (this->*m_updateFunc)(input);
}

void PlayerCube::OnHitObject(const InputState& input)
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
                        m_vec.y = kJumpRingJumpAcc;	// �W�����v�J�n
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
                            m_updateFunc = &PlayerCube::RevGravityUpdate;
                        }
                        else
                        {
                            m_isRevGravity = false; // �d�͐���
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
                else if (m_pStage->IsUnder(m_pos, tempPos, i, j) && object == ObjectType::Block)
                {
                    if (!m_isRevGravity)
                    {
                        m_angle = 0.0f;
                        m_vec.y = 0.0f;
                        m_pos.y = tempPos - Game::kBlockSize;
                        m_isField = true;
                    }
                    else
                    {
                        m_angle = 0.0f;
                        m_vec.y = 0.0f;
                        m_pos.y = tempPos;
                        m_isField = true;
                    }
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

void PlayerCube::Draw()
{
	DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);
	//DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);
}

void PlayerCube::NormalUpdate(const InputState& input)
{
    // �v���C���[�̋����̏���
    m_pos += m_vec;
    m_vec.y += kGravity;
    if (m_isMoveRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    // �n�ʂƂ̓����蔻��
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
            m_vec.y = kJumpAcc;	// �W�����v�J�n
        }
    }

    if (m_isDead)
    {
        m_updateFunc = &PlayerCube::DeadUpdate;
    }
}

void PlayerCube::RevGravityUpdate(const InputState& input)
{
    // �v���C���[�̋����̏���
    m_pos += m_vec;
    m_vec.y += -kGravity;
    if (m_isMoveRight) m_angle += -kRotaSpeed;
    else m_angle += kRotaSpeed;

    // �n�ʂƂ̓����蔻��
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
            m_vec.y = -kJumpAcc;	// �W�����v�J�n
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

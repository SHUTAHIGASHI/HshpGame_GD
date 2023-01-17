#include "playerCube.h"
#include "game.h"

namespace
{
    // �ړ����x
    constexpr float kMoveSpeed = 12.0f;

    // �摜�̉�]���x
    constexpr float kRotaSpeed = 0.2f;

    // �摜�̕\���ʒu
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;

    // �W�����v��
    constexpr float kJumpAcc = -24.0f;

    // �d��
    constexpr float kGravity = 2.0f;
}

PlayerCube::PlayerCube()
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

    // �n�ʂƂ̓����蔻��
    bool isField = false;

    if (m_pos.y > Game::kStageLowerLimit - m_height)
    {
        m_angle = 0;
        m_pos.y = Game::kStageLowerLimit - m_height;
        isField = true;
    }

    if (input.IsTriggered(InputType::space))
    {
        if (isField)
        {
            m_vec.y = kJumpAcc;	// �W�����v�J�n
        }
    }

    // ��ʒ[�ɍs�����Ƃ����ꍇ
    if (GetLeft() < 0)
    {
        m_pos.x = 0.0f;    // ��ʒ[��荶�ɂ͍s���Ȃ�
        m_vec.x *= -1;
    }
    if (GetRight() > Game::kScreenWidth)
    {
        m_pos.x = static_cast<float>(Game::kScreenWidth - m_width); // ��ʒ[���E�ɂ͍s���Ȃ�
        m_vec.x *= -1;
    }
    // �X�e�[�W�͈̔͊O�ɍs�����Ƃ����ꍇ
    if (GetBottom() > Game::kStageLowerLimit)
    {
        m_pos.y = static_cast<float>(Game::kStageLowerLimit - m_height);    // �X�e�[�W�͈̔͂�艺�ɂ͍s���Ȃ�
    }
}

void PlayerCube::Draw()
{
	DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);
	DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);
}

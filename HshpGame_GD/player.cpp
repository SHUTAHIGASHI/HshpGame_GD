#include "DxLib.h"
#include "player.h"
#include "game.h"

namespace
{
    // �ړ����x
    constexpr float kMoveSpeed = 12.0f;

    // �摜�̕\���ʒu
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;
}

Player::Player()
{
    m_height = 0;
    m_width = 0;

    m_isDead = false;
}

// �v���C���[�̏�����
void Player::init()
{
    // ���S����� false �ɐݒ�
    m_isDead = false;
    
    // �ړ��ʂ̏�����
    m_vec.x = 0;
    m_vec.y = kMoveSpeed;
}

// �v���C���[�̉摜�Z�b�g
void Player::setHandle(int playerHandle)
{
    // �摜�T�C�Y�̎擾
    GetGraphSize(m_handle, &m_width, &m_height);
}

// �v���C���[�̍��W�ݒ�
void Player::setPos(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
}

// �v���C���[�̍X�V����
void Player::update()
{
    // �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
    int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // ���݂̍��W�Ɉړ��ʂ�������
    m_pos += m_vec;

    // �L�[���͂��������ꍇ
    if (padState & PAD_INPUT_RIGHT) // �E
    {
        m_pos.x += kMoveSpeed;
    }
    if (padState & PAD_INPUT_LEFT)  // ��
    {
        m_pos.x += -kMoveSpeed;
    }

    // ��ʒ[�ɍs�����Ƃ����ꍇ
    if (getLeft() < 0)
    {
        m_pos.x = 0.0f;    // ��ʒ[��荶�ɂ͍s���Ȃ�
    }
    if (getRight() > Game::kScreenWidth)
    {
        m_pos.x = static_cast<float>(Game::kScreenWidth - m_width); // ��ʒ[���E�ɂ͍s���Ȃ�
    }
    // �X�e�[�W�͈̔͊O�ɍs�����Ƃ����ꍇ
    if (getTop() < Game::kStageUpperLimit)
    {
        m_pos.y = Game::kStageUpperLimit;   // �X�e�[�W�͈̔͂���ɂ͍s���Ȃ�
        m_vec.y *= -1;                      // �d�͕ύX
    }
    if (getBottom() > Game::kStageLowerLimit)
    {
        m_pos.y = static_cast<float>(Game::kStageLowerLimit - m_height);    // �X�e�[�W�͈̔͂�艺�ɂ͍s���Ȃ�
        m_vec.y *= -1;                      // �d�͕ύX
    }
}

// �v���C���[�̕`�揈��
void Player::draw()
{
    // �`��p�O���t�B�b�N�n���h��
    int handle = m_handle;

    // �`��p�x�p�ϐ�
    double angle = 0.0;
    
    // �v���C���[�`��
    DrawRotaGraphF(m_pos.x + kPlayerDrawPosX, m_pos.y + kPlayerDrawPosY, 1.0, angle, handle, true, false);
}
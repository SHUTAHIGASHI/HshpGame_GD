#pragma once
#include "Vec2.h"

// �v���C���[�N���X
class PlayerBase
{
public:
	PlayerBase() :
		m_handle(-1),
		m_deathEffectHandle(-1),
		m_height(0),
		m_width(0),
		m_effectHeight(0),
		m_effectWidth(0),
		m_countFrame(0),
		m_angle(0.0f),
		m_isRotaRight(true),
		m_isRevGravity(false),
		m_isField(false),
		m_pos(),
		m_vec(),
		m_isScroll(false),
		m_isStageClear(false),
		m_isDead(false)
	{
	}
	virtual ~PlayerBase() {}

	// �v���C���[�̒��S���W�擾
	virtual float GetCenterX() const { return m_pos.x + (m_width / 2); }
	virtual float GetCenterY() const { return m_pos.y + (m_height / 2); }

	// m_isGameClear ���擾
	virtual bool IsStageClear() const { return m_isStageClear; }
	// m_isDead �� true �ɂ���
	virtual void SetDead() { m_isDead = true; }
	// m_isDead ���擾
	virtual bool IsDead() const { return m_isDead; }

	// �����蔻��p�Ɏl�����̍��W�擾�@
	virtual float GetLeft()	const { return m_pos.x; }
	virtual float GetRight() const { return m_pos.x + static_cast<float>(m_width); }
	virtual float GetTop() const { return m_pos.y; }
	virtual float GetBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// �v���C���[�̍��W�擾
	Vec2 GetPos() const { return m_pos; }

	virtual bool IsRevGravity() const { return m_isRevGravity; }

protected:
	// �摜�f�[�^
	int m_handle;
	int m_deathEffectHandle;

	// �摜�T�C�Y
	float m_height;
	float m_width;
	// �G�t�F�N�g�摜�T�C�Y
	float m_effectHeight;
	float m_effectWidth;
	// �t���[�������J�E���g
	int m_countFrame;

	// �摜�\���p�x
	float m_angle;
	// �ړ�����
	bool m_isRotaRight;
	// �d�͕���
	bool m_isRevGravity;

	// �n�ʂƂ̓����蔻��p�ϐ�
	bool m_isField;

	// �v���C���[���W
	Vec2 m_pos;
	// �ړ���
	Vec2 m_vec;

	bool m_isScroll;

	// �S�[������
	bool m_isStageClear;
	// ���S����
	bool m_isDead;
};
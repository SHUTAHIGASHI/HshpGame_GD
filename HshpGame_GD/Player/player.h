#pragma once
#include "Vec2.h"

// �v���C���[�N���X
class Player
{
public:
	Player();
	virtual ~Player() {}

	// �v���C���[�̏�����
	virtual void Init();
	// �v���C���[�̉摜�Z�b�g
	virtual void SetHandle(int playerHandle);

	// �v���C���[�̍X�V����
	virtual void Update();
	// �v���C���[�̕`�揈��
	virtual void Draw();
	
	// �v���C���[�̒��S���W�擾
	virtual float GetCenterX(){ return m_pos.x + (m_width / 2); }
	virtual float GetCenterY(){ return m_pos.y + (m_height / 2); }

	// m_isGameClear ���擾
	virtual bool IsStageClear() { return m_isStageClear; }
	// m_isDead �� true �ɂ���
	virtual void SetDead() { m_isDead = true; }
	// m_isDead ���擾
	virtual bool IsDead() { return m_isDead; }

	// �����蔻��p�Ɏl�����̍��W�擾�@
	virtual float GetLeft()	const { return m_pos.x; }
	virtual float GetRight()	const { return m_pos.x + static_cast<float>(m_width); }
	virtual float GetTop()	const { return m_pos.y; }
	virtual float GetBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// �v���C���[�̍��W�擾
	Vec2 GetPos() const { return m_pos; }

	virtual bool IsRevGravity() { return m_isRevGravity; }

protected:
	// �摜�f�[�^
	int m_handle;

	// �摜�T�C�Y
	float m_height;
	float m_width;

	// �摜�\���p�x
	float m_angle;

	// �ړ�����
	bool m_isMoveRight;
	// �d�͕���
	bool m_isRevGravity;

	// �n�ʂƂ̓����蔻��p�ϐ�
	bool m_isField;

	// �v���C���[���W
	Vec2 m_pos;

	// �ړ���
	Vec2 m_vec;

	// �S�[������
	bool m_isStageClear;

	// ���S����
	bool m_isDead;
};
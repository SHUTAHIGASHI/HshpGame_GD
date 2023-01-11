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

	// m_isDead �� true �ɂ���
	virtual void SetDead() { m_isDead = true; }
	// m_isDead ���擾
	virtual bool IsDead() { return m_isDead; }

	// �����蔻��p�Ɏl�����̍��W�擾�@
	float GetLeft()	const { return m_pos.x; }
	float GetRight()	const { return m_pos.x + static_cast<float>(m_width); }
	float GetTop()	const { return m_pos.y; }
	float GetBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// �v���C���[�̍��W�擾
	Vec2 GetPos() const { return m_pos; }

private:
	// �摜�f�[�^
	int m_handle;

	// �摜�T�C�Y
	int m_height;
	int m_width;

	// �\���ʒu
	Vec2 m_pos;

	// �ړ���
	Vec2 m_vec;

	// ���S����
	bool m_isDead;
};
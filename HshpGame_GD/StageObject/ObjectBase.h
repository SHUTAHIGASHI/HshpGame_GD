#pragma once

#include "game.h"

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase() {}

	virtual void Init();

	virtual void SetPos();

	virtual void Update();

	virtual void Draw();

	virtual bool CollisionCheck(float X, float Y);

	// �v���C���[�̒��S���W�擾
	virtual float GetCenterX() { return m_pos.x + (Game::kBlockSize / 2); }
	virtual float GetCenterY() { return m_pos.y + (Game::kBlockSize / 2); }

	// �����蔻��p�Ɏl�����̍��W�擾�@
	virtual float GetLeft()	{ return m_pos.x; }
	virtual float GetRight() { return m_pos.x + Game::kBlockSize; }
	virtual float GetTop() { return m_pos.y; }
	virtual float GetBottom() { return m_pos.y + Game::kBlockSize; }

	virtual Vec2 GetPos() { return m_pos; }
protected:
	// �u���b�N�\���ʒu
	Vec2 m_pos;

	// �摜�n���h��
	int m_hObjectImg;
	// �摜�T�C�Y
	float m_height;
	float m_width;
};


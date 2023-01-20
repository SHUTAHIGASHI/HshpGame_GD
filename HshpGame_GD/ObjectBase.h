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

	// �����蔻��p�Ɏl�����̍��W�擾�@
	virtual float GetLeft()	const { return m_pos.x; }
	virtual float GetRight()	const { return m_pos.x + Game::kBlockSize; }
	virtual float GetTop()	const { return m_pos.y; }
	virtual float GetBottom() const { return m_pos.y + Game::kBlockSize; }

	virtual Vec2 GetPos() const { return m_pos; }
protected:
	// �u���b�N�\���ʒu
	Vec2 m_pos;

};


#pragma once

#include "game.h"

enum class ObjectType
{
	Block,
	Spike,
	End
};

class MapObject
{
public:
	MapObject();
	~MapObject() {}

	void Init();

	void Update();

	void Draw();

	bool CollisionCheck(float X, float Y);

	// �����蔻��p�Ɏl�����̍��W�擾�@
	float GetLeft()	const { return m_pos.x; }
	float GetRight()	const { return m_pos.x + Game::kBlockSize; }
	float GetTop()	const { return m_pos.y; }
	float GetBottom() const { return m_pos.y + Game::kBlockSize; }
private:

	// �u���b�N�\���ʒu
	Vec2 m_pos;


};


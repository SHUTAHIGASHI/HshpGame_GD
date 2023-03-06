#pragma once
#include "Vec2.h"

class ParticleBase
{
public:
	ParticleBase();
	virtual ~ParticleBase();

	void init();

	virtual void update();
	virtual void draw();

	// �J�n	�Ƃ肠���������ʒu�̂ݐݒ�	���̂͌ʐݒ�
	void start(Vec2 pos);

	// �ݒ�\�ȍ���
	void setPos(Vec2 pos) { m_pos = pos; }
	void setVec(Vec2 vec) { m_vec = vec; }
	void setRadius(float r) { m_radius = r; }
	void setColor(unsigned int color) { m_color = color; }
	void setGravity(float gravity) { m_gravity = gravity; }
	void setAlphaDec(int dec) { m_alphaDec = dec; }
	void setRadiusAcc(float acc) { m_radiusAcc = acc; }

	bool isExist() const { return m_isExist; }

protected:
	Vec2 m_pos;
	Vec2 m_vec;
	float m_radius;
	unsigned int m_color;
	int m_alpha;
	bool m_isExist;

	// �d�͉����x	�����Ȃ��ꍇ��0.0���w�肷��
	float m_gravity;

	// �����x�̌������x	����255����w�肵���������Ă���
	int m_alphaDec;

	// ���a�̕ω���
	float m_radiusAcc;
};


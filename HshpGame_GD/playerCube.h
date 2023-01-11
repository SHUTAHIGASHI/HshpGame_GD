#include "player.h"


class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	// �v���C���[�̏�����
	void Init(int playerHandle);

	// �v���C���[�̍X�V����
	void Update();
	// �v���C���[�̕`�揈��
	void Draw();
private:
	// �摜�f�[�^
	int m_handle;

	// �摜�T�C�Y
	float m_height;
	float m_width;

	// �\���ʒu
	Vec2 m_pos;

	// �ړ���
	Vec2 m_vec;

	// �摜�p�x
	double m_angle;

	// ���S����
	bool m_isDead;
};

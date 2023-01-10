#include "player.h"


class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	// �v���C���[�̏�����
	void Init();
	// �v���C���[�̉摜�Z�b�g
	void SetHandle(int playerHandle);

	// �v���C���[�̍X�V����
	void Update();
	// �v���C���[�̕`�揈��
	void Draw();
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

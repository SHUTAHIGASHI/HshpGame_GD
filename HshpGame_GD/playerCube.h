#include "game.h"
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
	void Update(const InputState& input);
	// �v���C���[�̕`�揈��
	void Draw();
};

#include "game.h"
#include "player.h"

class ObjectBlock;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setObject(ObjectBlock* Object) { pObject = Object; }

	// �v���C���[�̏�����
	void Init(int playerHandle);

	// �v���C���[�̍X�V����
	void Update(const InputState& input);
	// �v���C���[�̕`�揈��
	void Draw();

private:
	ObjectBlock* pObject;
};

#include "game.h"
#include "player.h"

class MapObject;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setObject(MapObject* Object) { pObject = Object; }

	// �v���C���[�̏�����
	void Init(int playerHandle);

	// �v���C���[�̍X�V����
	void Update(const InputState& input);
	// �v���C���[�̕`�揈��
	void Draw();

private:
	MapObject* pObject;
};

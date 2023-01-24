#include "game.h"
#include "player.h"

class Stage;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setStage(Stage* stage) { pStage = stage; }

	// �v���C���[�̏�����
	void Init(int playerHandle);

	// �v���C���[�̍X�V����
	void Update(const InputState& input);

	void OnHitObject(const InputState& input);
	
	// �v���C���[�̕`�揈��
	void Draw();
private:
	Stage* pStage;
};

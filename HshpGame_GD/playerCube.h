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
	void NormalUpdate(const InputState& input);
	// �v���C���[���S���̍X�V����
	void DeadUpdate();

	// �I�u�W�F�N�g�Ɠ����������̏���
	void OnHitObject(const InputState& input);
	
	// �v���C���[�̕`�揈��
	void Draw();
private:
	// �X�e�[�W�̃|�C���^
	Stage* pStage;
};

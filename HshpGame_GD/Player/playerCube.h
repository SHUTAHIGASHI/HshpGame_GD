#include "game.h"
#include "player.h"

class Stage;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setStage(Stage* stage) { m_pStage = stage; }

	// �v���C���[�̏�����
	void Init(int playerHandle);

	// �v���C���[�̍X�V����
	void Update(const InputState& input);

	// �I�u�W�F�N�g�Ɠ����������̏���
	void OnHitObject(const InputState& input);
	
	// �v���C���[�̕`�揈��
	void Draw();
private:
	// �X�e�[�W�̃|�C���^
	Stage* m_pStage;

	void NormalUpdate(const InputState& input);
	// �v���C���[���S���̍X�V����
	void DeadUpdate(const InputState& input);

	using UpdateFunc_t = void (PlayerCube::*) (const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;
};

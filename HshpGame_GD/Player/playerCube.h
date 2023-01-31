#include "game.h"
#include "playerBase.h"

class Stage;

class PlayerCube :
    public PlayerBase
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void SetStage(Stage* stage) { m_pStage = stage; }

	// �v���C���[�̏�����
	void Init(int playerHandle, int playerDeathEffect);

	// �v���C���[�̍X�V����
	void Update(const InputState& input);

	// �I�u�W�F�N�g�Ɠ����������̏���
	void OnHitObject(const InputState& input);
	
	// �v���C���[�̕`�揈��
	void Draw();

	void ChangeUpdateType();

	void SetSpawn();

	// �E��]���邩�ǂ����̐ݒ�
	void SetRotaRight(bool isRight) { m_isRotaRight = isRight; }
	bool IsRotaRight() const { return m_isRotaRight; }

	void SetPlayerVec(int scroll);
	void DeleteVecX() { m_vec.x = 0.0f; }
private:
	// �X�e�[�W�̃|�C���^
	Stage* m_pStage;

	// �ʏ펞�̍X�V����
	void NormalUpdate(const InputState& input);
	// �d�͔��]���̍X�V����
	void RevGravityUpdate(const InputState& input);
	// �X�e�[�W�X�N���[�����̍X�V����
	void StageScrollUpdate(const InputState& input);
	// �v���C���[���S���̍X�V����
	void DeadUpdate(const InputState& input);

	using m_tUpdateFunc = void (PlayerCube::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
};

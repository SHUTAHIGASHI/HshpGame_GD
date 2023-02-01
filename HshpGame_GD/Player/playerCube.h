#include "game.h"
#include "playerBase.h"

class Stage;

enum class PlayerState
{
	Cube,
	Ship
};

class PlayerCube :
    public PlayerBase
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void SetStage(Stage* stage) { m_pStage = stage; }

	// �v���C���[�̏�����
	void Init(int playerHandle, int playerDeathEffect);

	void SetPlayerInfo();

	// �v���C���[�̍X�V����
	void Update(const InputState& input);

	// �I�u�W�F�N�g�Ɠ����������̏���
	void OnHitObject(const InputState& input);
	
	// �v���C���[�̕`�揈��
	void Draw();

	void ChangeUpdateType();

	void SetSpawnPos();

	// �E��]���邩�ǂ����̐ݒ�
	void SetRotaRight(bool isRight) { m_isRotaRight = isRight; }
	bool IsRotaRight() const { return m_isRotaRight; }

	void SetPlayerVec(int scroll);
	void DeleteVecX() { m_vec.x = 0.0f; }

	PlayerState GetPlayerState() const { return m_playerState; }
private:
	PlayerState m_playerState;
	
	// �X�e�[�W�̃|�C���^
	Stage* m_pStage;

	// �L���[�u�̒ʏ펞�̍X�V����
	void CubeNormalUpdate(const InputState& input);
	// �L���[�u�̏d�͔��]���̍X�V����
	void CubeRevGravityUpdate(const InputState& input);
	// �V�b�v�̒ʏ펞�̍X�V����
	void ShipNormalUpdate(const InputState& input);
	// �V�b�v�̏d�͔��]���̍X�V����
	void ShipRevGravityUpdate(const InputState& input);
	// �v���C���[���S���̍X�V����
	void DeadUpdate(const InputState& input);

	using m_tUpdateFunc = void (PlayerCube::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
};

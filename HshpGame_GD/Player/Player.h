#include "game.h"

class Stage;

enum class PlayerState
{
	Cube,
	Wave
};

class Player
{
public:
	Player() :
		m_playerState(PlayerState::Cube),
		m_pStage(nullptr),
		m_updateFunc(&Player::CubeNormalUpdate),
		m_pos(),
		m_vec(),
		m_lastPos(),
		m_hPlayer(-1),
		m_hWaveBurner(-1),
		m_hDeathEffect(-1),
		m_hDeathSound(-1),
		m_playerScale(0.0),
		m_effectHeight(0),
		m_effectWidth(0),
		m_angle(0.0f),
		m_lastAngle(),
		m_countFrame(0),
		m_deathCountFrame(0),
		m_isMoveRight(true),
		m_isRevGravity(false),
		m_isDashRingEnabled(false),
		m_isField(false),
		m_isScroll(false),
		m_isStageClear(false),
		m_isDead(false)
	{}
	virtual ~Player() {}

	void SetStage(Stage* stage) { m_pStage = stage; }

	// �v���C���[�̏�����
	void Init(int playerHandle, int waveBurner, int playerDeathEffect, int hDeathSound);

	// �v���C���[�̃X�|�[���ʒu���Z�b�g
	void SetSpawnPos();

	// �����o�֐��|�C���^�̒��g��ύX
	void ChangeUpdateType();
	// �v���C���[�̍X�V����
	void Update(const InputState& input);

	// �I�u�W�F�N�g�Ɠ����������̏���
	void OnHitObject(const InputState& input);
	
	// �v���C���[�̕`�揈��
	void Draw();

	// �v���C���[�̈ړ����̃G�t�F�N�g
	void DrawMoveEffect();

	// �E�ړ����邩�ǂ����̐ݒ�
	void SetMoveRight(bool isRight) { m_isMoveRight = isRight; }
	// �E�ړ����邩�ǂ����擾
	bool IsMoveRight() const { return m_isMoveRight; }

	// �d�͔��]���Ă��邩���擾
	bool IsRevGravity() const { return m_isRevGravity; }

	// ��ʃX�N���[�����̉��ړ��̐؂�ւ�
	void SetPlayerVec(int scroll);
	// �������̃x�N�g���폜
	void DeleteVecX() { m_vec.x = 0.0f; }

	// �v���C���[�̌��݂̏�Ԃ��擾
	PlayerState GetPlayerState() const { return m_playerState; }

	// �l�����̎擾
	float GetLeft() const { return m_pos.x; }
	float GetTop() const { return m_pos.y; }
	float GetRight() const { return m_pos.x + Game::kBlockSize; }
	float GetBottom() const { return m_pos.y + Game::kBlockSize; }

	// �v���C���[�̒��S���W�擾
	float GetCenterX() const { return m_pos.x + (Game::kBlockSize / 2); }	// �L���[�u�̒��S
	float GetCenterY() const { return m_pos.y + (Game::kBlockSize / 2); }

	// �N���A�������ǂ������擾
	bool IsStageClear() const { return m_isStageClear; }
	// ���S����� true �ɂ���
	void SetDead() { m_isDead = true; }
	// ���S������擾
	bool IsDead() const { return m_isDead; }

	// �v���C���[�̍��W�擾
	Vec2 GetPos() const { return m_pos; }

private:
	// ���݂̃v���C���[�̏��
	PlayerState m_playerState;
	
	// �X�e�[�W�̃|�C���^
	Stage* m_pStage;

	// �L���[�u�̒ʏ펞�̍X�V����
	void CubeNormalUpdate(const InputState& input);
	// �L���[�u�̏d�͔��]���̍X�V����
	void CubeRevGravityUpdate(const InputState& input);
	// �V�b�v�̒ʏ펞�̍X�V����
	void WaveUpdate(const InputState& input);
	// �v���C���[���S���̍X�V����
	void GoalUpdate(const InputState& input);

	using m_tUpdateFunc = void (Player::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	// �v���C���[���W
	Vec2 m_pos;
	// �ړ���
	Vec2 m_vec;

	Vec2 m_lastPos[5];

	// �摜�f�[�^
	int m_hPlayer;
	int m_hWaveBurner;
	int m_hDeathEffect;

	// ���f�[�^
	int m_hDeathSound;

	// �v���C���[�̃T�C�Y
	double m_playerScale;

	// �G�t�F�N�g�摜�T�C�Y
	float m_effectHeight;
	float m_effectWidth;
	// �摜�\���p�x
	double m_angle;
	double m_lastAngle[5];

	// �t���[�������J�E���g
	int m_countFrame;
	int m_deathCountFrame;

	// �ړ�����
	bool m_isMoveRight;
	// �d�͕���
	bool m_isRevGravity;
	// �_�b�V�������O�p�̔���
	bool m_isDashRingEnabled;
	// �n�ʂƂ̓����蔻��p�ϐ�
	bool m_isField;
	// �X�N���[�������ǂ���
	bool m_isScroll;

	// �S�[������
	bool m_isStageClear;
	// ���S����
	bool m_isDead;
};

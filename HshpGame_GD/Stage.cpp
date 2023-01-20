#include "Stage.h"
#include "game.h"

Stage::Stage() :
	m_pos(),
	m_vec()
{

}

void Stage::Init()
{
	m_vec.x = -Game::kMoveSpeed;
	m_vec.y = 0.0f;
	
	m_pos.x = Game::kStageLowerLimit;
	m_pos.y = Game::kStageLowerLimit;
	
	
	m_Object.Init();
	m_Object.SetPos(Game::kScreenWidthHalf, Game::kStageLowerLimit - Game::kBlockSize);
}

void Stage::Update()
{	
	m_Object.Update();
}

void Stage::Draw()
{
	// �X�e�[�W�̐��̕\��
	DrawLine(0, Game::kStageUpperLimit, Game::kScreenWidth, Game::kStageUpperLimit, 0xffffff);

	int stageColor = 0x40e0d0;

	DrawBox(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit + Game::kBlockSize, stageColor, true);

	stageColor = 0xe0ffff;

	DrawLine(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit, stageColor, true);
	DrawLine(0, Game::kStageLowerLimit + Game::kBlockSize, Game::kScreenWidth, Game::kStageLowerLimit + Game::kBlockSize, stageColor, true);
	
	// �X�e�[�W�M�~�b�N�̕`��
	m_Object.Draw();
}

bool Stage::CollisionCheck(Vec2 playerPos)
{
	// �������Ă��Ȃ��ꍇ�������X�L�b�v
	if (m_Object.GetRight() <= playerPos.x) return false;
	if (playerPos.x + Game::kBlockSize <= m_Object.GetLeft()) return false;
	if (m_Object.GetBottom() <= playerPos.y) return false;
	if (playerPos.y + Game::kBlockSize <= m_Object.GetTop()) return false;

	// �������Ă���ꍇ�v���C���[�����S����ɂ���
	return true;
}

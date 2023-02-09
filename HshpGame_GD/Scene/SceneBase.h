#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	// ������
	virtual void Init() {}
	// �폜
	virtual void End() {}
	// �X�V
	virtual void Update() {}
	// �`��
	virtual void Draw() {}

	// �V�[���I��
	virtual bool IsEnd() { return false; }
};
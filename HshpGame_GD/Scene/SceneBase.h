#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase():
	m_isEnd(false)
	{}
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
	virtual bool IsEnd() { return m_isEnd; }

protected:
	bool m_isEnd;
};
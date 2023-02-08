#pragma once
#include "SceneBase.h"
#include "game.h"

class SceneClear : public SceneBase
{
public:
	SceneClear()
	{
		titleDelay = 0;
		
		m_isEnd = false;

		m_width = 0;
		m_height = 0;
	}
	virtual ~SceneClear() {}

	// ������
	virtual void Init();
	
	// �I������
	void end();
	// �X�V
	virtual void Update(NextSceneState& nextScene);
	// �`��
	virtual void Draw();

	// m_isEnd ���擾
	virtual bool IsEnd() { return m_isEnd; }
private:
	// �^�C�g���\���܂ł̒x���p�ϐ�
	int titleDelay;
	
	// �V�[���I��
	bool m_isEnd;

	// �摜�T�C�Y
	int m_width;
	int m_height;
};
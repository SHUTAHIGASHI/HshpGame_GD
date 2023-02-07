#pragma once
#include "SceneBase.h"
#include "InputState.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle():
		m_selectPos(0)
	{
		m_TextPosY = 0;
		m_TextVecY = 0;

		m_isEnd = false;

		m_hBackgroundGraphic = -1;
	}
	virtual ~SceneTitle() {}

	// ������
	virtual void init();
	
	// �I������
	void end();

	// �X�V����
	virtual void update(const InputState& input, bool &isGameEnd);
	// �`��
	virtual void draw();

	// m_isEnd ���擾
	virtual bool isEnd() { return m_isEnd; }
private:	
	// ���j���[�I��
	int m_selectPos;
	
	// �e�L�X�g�\���ʒu�ύX
	int m_TextPosY;
	int m_TextVecY;

	// �^�C�g���\�����I���邩�ǂ���
	bool m_isEnd;

	// �摜�f�[�^
	int m_hBackgroundGraphic;
};
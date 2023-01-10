#pragma once

enum class InputType
{
	next, // ���֍s���{�^��
	pause, // �|�[�Y�{�^��
	right,	// �E
	left,	// ��
	up,		// ��
	down,	// ��
	space
};

class InputState
{
private:
	int keyPadState;
	int lastKeyPadState;
	char keyState[256];
	char lastKeyState[256];

public:
	bool IsTriggered(InputType type)const;
	bool IsPressed(InputType type)const;
	void Update();
};
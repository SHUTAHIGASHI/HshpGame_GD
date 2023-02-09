#pragma once

enum class InputType
{
	escape,
	enter, // ���֍s���{�^��
	space,
	pause, // �|�[�Y�{�^��
	right,	// �E
	left,	// ��
	up,		// ��
	down,	// ��
	jump,
	retry,
	end
};

class InputState
{
private:
	char keyMouseState[256];
	char lastKeyMouseState[256];
	char keyState[256];
	char lastKeyState[256];

public:
	bool IsTriggered(InputType type)const;
	bool IsPressed(InputType type)const;
	void Update();
};
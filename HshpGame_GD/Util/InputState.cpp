#include "InputState.h"
#include <DxLib.h>

void InputState::Update()
{
	// �O�̃t���[���̃L�[�󋵂��R�s�[
	for (int i = 0; i < _countof(lastKeyState); ++i)
	{
		lastKeyState[i] = keyState[i];
	}
	for (int i = 0; i < _countof(lastKeyMouseState); ++i)
	{
		lastKeyMouseState[i] = keyMouseState[i];
		keyMouseState[i] = GetMouseInput();
	}

	GetHitKeyStateAll(keyState);
}

bool InputState::IsTriggered(InputType type)const
{
	if (type == InputType::escape)
	{
		return !lastKeyState[KEY_INPUT_ESCAPE] &&
			keyState[KEY_INPUT_ESCAPE];
	}
	else if (type == InputType::enter)
	{
		return !lastKeyState[KEY_INPUT_RETURN] &&
			keyState[KEY_INPUT_RETURN];
	}
	else if (type == InputType::space)
	{
		return !lastKeyState[KEY_INPUT_SPACE] &&
			keyState[KEY_INPUT_SPACE];
	}
	else if (type == InputType::pause)
	{
		return !lastKeyState[KEY_INPUT_P] &&
			keyState[KEY_INPUT_P];
	}
	else if (type == InputType::right)
	{
		return !lastKeyState[KEY_INPUT_RIGHT] &&
			keyState[KEY_INPUT_RIGHT];
	}
	else if (type == InputType::left)
	{
		return !lastKeyState[KEY_INPUT_LEFT] &&
			keyState[KEY_INPUT_LEFT];
	}
	else if (type == InputType::up)
	{
		return !lastKeyState[KEY_INPUT_UP] &&
			keyState[KEY_INPUT_UP];
	}
	else if (type == InputType::down)
	{
		return !lastKeyState[KEY_INPUT_DOWN] &&
			keyState[KEY_INPUT_DOWN];
	}
	else if (type == InputType::jump)
	{
		return !lastKeyState[KEY_INPUT_SPACE] &&
			keyState[KEY_INPUT_SPACE] ||
			!lastKeyState[KEY_INPUT_UP] &&
			keyState[KEY_INPUT_UP] ||
			!lastKeyMouseState[MOUSE_INPUT_LEFT] &&
			keyMouseState[MOUSE_INPUT_LEFT];
	}
	else if (type == InputType::retry)
	{
		return !lastKeyState[KEY_INPUT_R] &&
			keyState[KEY_INPUT_R];
	}

	return false;
}

bool InputState::IsPressed(InputType type)const
{
	if (type == InputType::enter)
	{
		return keyState[KEY_INPUT_RETURN];
	}
	else if (type == InputType::jump)
	{
		return keyState[KEY_INPUT_SPACE] ||
			keyState[KEY_INPUT_UP] ||
			keyMouseState[MOUSE_INPUT_LEFT];
	}
	return false;
}
#pragma once

enum class InputType
{
	next, // 次へ行くボタン
	pause, // ポーズボタン
	right,	// 右
	left,	// 左
	up,		// 上
	down,	// 下
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
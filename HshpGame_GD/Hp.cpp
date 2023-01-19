#include "game.h"
#include "Hp.h"
#include "InputState.h"

Hp::Hp() :
	hp(0)
{
}

void Hp::init()
{
	hp = 500;
}

void Hp::update(const InputState& input)
{
	if (input.IsPressed(InputType::up))
	{
		hp--;
	}
}

void Hp::draw()
{
	DrawBox(0, 0, hp, 30, 0xFF0000, true);
	DrawBox(0, 0, 500, 30, 0xFFFFFF, false);
}

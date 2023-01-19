#pragma once
class Hp
{
public:
	Hp();
	~Hp(){}

	void init();

	void update(const InputState& input);

	void draw();
private:
	int hp;
};


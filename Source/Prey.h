#pragma once
#include "Map.h"
#include "Obj.h"

// �S����Ȃ����̻���(Prey = �ǂ������)
#define PREYSIZE_X GRIDSIZE
#define PREYSIZE_Y GRIDSIZE * 1.5



class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	void Draw(void);

private:
	bool Init(void);
};


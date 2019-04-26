#include <DxLib.h>
#include "Prey.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	// player(‹SˆÈŠO)‚ÌÎß¼Þ¼®Ý‚Ì¾¯Ä
	SetPos(pos);
}


Prey::~Prey()
{
}

void Prey::Move(const Controller & controll, WeakList objlist)
{

}

void Prey::Draw(void)
{
	DrawBox(pos.x, pos.y, pos.x + GRIDSIZE, pos.y - (GRIDSIZE + 40), 0xff0000, true);
}

bool Prey::Init(void)
{

	return true;
}

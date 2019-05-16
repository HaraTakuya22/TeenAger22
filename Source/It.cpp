#include "It.h"


It::It()
{
}

It::It(VECTOR2 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	// ‹S‚ÌÎß¼Þ¼®Ý‚Ì¾¯Ä
	SetPos(pos);
}


It::~It()
{
}

void It::Draw(void)
{

}

void It::Move(const Controller & controll, WeakList objlist)
{

}

bool It::Init(void)
{
	return true;
}

#include "It.h"


It::It()
{
}

It::It(VECTOR2 pos,TYPE_NUM i_num)
{
	/*this->pos[i_num].x = pos[i_num].x;
	this->pos[i_num].y = pos[i_num].y;*/

	// �S���߼޼�݂̾��
	//SetPos(pos[i_num]);
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

bool It::Init(TYPE_NUM i_num)
{
	return true;
}

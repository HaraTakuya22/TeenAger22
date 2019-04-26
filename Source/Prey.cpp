#include <DxLib.h>
#include "Prey.h"
#include "Controller.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	//		MAIN			
	keyIdTbl = { KEY_INPUT_NUMPAD2,	// ��
				 KEY_INPUT_NUMPAD4,	// ��
				 KEY_INPUT_NUMPAD6,	// �E
				 KEY_INPUT_NUMPAD8,	// ��
	};
	//	MAIN	
	posTbl = { &pos.y, &pos.x,	// ��
				&pos.x,	&pos.y, // ��
				&pos.x,	&pos.y, // �E
				&pos.y,	&pos.x, // ��
	};
	//			MAIN
	speedTbl = { PLAYER_DEF_SPEED,	// ��
				 -PLAYER_DEF_SPEED,	// ��
				 PLAYER_DEF_SPEED,	// �E
				 -PLAYER_DEF_SPEED,	// ��
	};
	//	MAIN		OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,	DIR_UP,		DIR_LEFT,	DIR_RIGHT,	// ���i��E���E�E�j
				DIR_LEFT,	DIR_RIGHT,	DIR_DOWN,	DIR_UP,		// ���i�E�E���E��j
				DIR_RIGHT,	DIR_LEFT,	DIR_DOWN,	DIR_UP,		// �E�i���E���E��j
				DIR_UP,		DIR_DOWN,	DIR_LEFT,	DIR_RIGHT,	// ��i���E���E�E�j
	};
	// player(�S�ȊO)���߼޼�݂̾��
	SetPos(pos);
}


Prey::~Prey()
{
}

void Prey::Move(const Controller & controll, WeakList objlist)
{
	auto &keyTbl = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto &keyTblOld = controll.GetButtonInfo(KEY_TYPE_OLD);

}

void Prey::Draw(void)
{
	DrawBox(pos.x, pos.y, pos.x + GRIDSIZE, pos.y - (GRIDSIZE + 40), 0xff0000, true);
}

bool Prey::Init(void)
{

	return true;
}

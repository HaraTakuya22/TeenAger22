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
	keyIdTbl = { KEY_INPUT_NUMPAD2,	// 下
				 KEY_INPUT_NUMPAD4,	// 左
				 KEY_INPUT_NUMPAD6,	// 右
				 KEY_INPUT_NUMPAD8,	// 上
	};
	//	MAIN	
	posTbl = { &pos.y, &pos.x,	// 下
				&pos.x,	&pos.y, // 左
				&pos.x,	&pos.y, // 右
				&pos.y,	&pos.x, // 上
	};
	//			MAIN
	speedTbl = { PLAYER_DEF_SPEED,	// 下
				 -PLAYER_DEF_SPEED,	// 左
				 PLAYER_DEF_SPEED,	// 右
				 -PLAYER_DEF_SPEED,	// 上
	};
	//	MAIN		OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,	DIR_UP,		DIR_LEFT,	DIR_RIGHT,	// 下（上・左・右）
				DIR_LEFT,	DIR_RIGHT,	DIR_DOWN,	DIR_UP,		// 左（右・下・上）
				DIR_RIGHT,	DIR_LEFT,	DIR_DOWN,	DIR_UP,		// 右（左・下・上）
				DIR_UP,		DIR_DOWN,	DIR_LEFT,	DIR_RIGHT,	// 上（下・左・右）
	};
	// player(鬼以外)のﾎﾟｼﾞｼｮﾝのｾｯﾄ
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

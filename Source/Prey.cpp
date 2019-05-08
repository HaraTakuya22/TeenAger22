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

	//			MAIN			
	keyIdTbl = { KEY_INPUT_NUMPAD2,	// 下
				 KEY_INPUT_NUMPAD4,	// 左
				 KEY_INPUT_NUMPAD6,	// 右
				 KEY_INPUT_NUMPAD8,	// 上
	};
	//			MAIN	
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
	//			MAIN		OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,	DIR_UP,		DIR_LEFT,	DIR_RIGHT,	// 下（上・左・右）
				DIR_LEFT,	DIR_RIGHT,	DIR_DOWN,	DIR_UP,		// 左（右・下・上）
				DIR_RIGHT,	DIR_LEFT,	DIR_DOWN,	DIR_UP,		// 右（左・下・上）
				DIR_UP,		DIR_DOWN,	DIR_LEFT,	DIR_RIGHT,	// 上（下・左・右）
	};

	PassageTbl = {
		true,	//PASSAGE_WAY
		false,	//PASSAGE_WALL
	};

	// player(鬼以外)のﾎﾟｼﾞｼｮﾝのｾｯﾄ
	SetPos(pos);
	Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	Prey::Init();
	afterKeyFlag = false;
}


Prey::~Prey()
{
}

void Prey::Move(const Controller & controll, WeakList objlist)
{
	auto &keyTbl = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto &keyTblOld = controll.GetButtonInfo(KEY_TYPE_OLD);

	auto SidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlag) {
		VECTOR2 side;
		switch (dir)
		{
		case DIR_LEFT:
			side = { speed - (sideFlag ^ 1), 0 };
			break;
		case DIR_RIGHT:
			side = { speed + (GRIDSIZE - sideFlag), 0 };
			break;
		case DIR_DOWN:
			side = { 0, speed + (GRIDSIZE - sideFlag) };
			break;
		case DIR_UP:
			side = { 0, speed - (sideFlag ^ 1) };
			break;
		}
		return pos + side;
	};

	auto move = [&, dir = Prey::dir](DIR_TBL_ID id){
		if (keyTbl[keyIdTbl[dirTbl[Prey::dir][id]]])
		{
			// 方向のｾｯﾄ
			Prey::dir = dirTbl[dir][id];
			if (!PassageTbl[static_cast<int>(lpMap.GetMapData(SidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
			{
				// 壁が隣にあった場合
				return false;
			}
			else
			{
				// 補正処理
				if ((*posTbl[Prey::dir][TBL_SUB]) % GRIDSIZE)
				{
					(*posTbl[Prey::dir][TBL_SUB]) = (((*posTbl[Prey::dir][TBL_SUB] + GRIDSIZE / 2) / GRIDSIZE) * GRIDSIZE);
				}
			}
			// 移動処理
			if (!(*posTbl[Prey::dir][TBL_SUB] % GRIDSIZE))
			{
				(*posTbl[Prey::dir][TBL_MAIN]) += speedTbl[Prey::dir];
				return true;
			}
		}
		return false;
	};

	//if (!(move((DIR_TBL_ID)(DIR_TBL_SUB1 - (afterKeyFlag << 1)))
	//	|| move((DIR_TBL_ID)(DIR_TBL_SUB2 - (afterKeyFlag << 1)))))	// ｼﾌﾄ演算でafterKeyFlagを1ﾄﾞｯﾄずらす
	//{
	//	afterKeyFlag = false;
	//	if (!(move((DIR_TBL_ID)(DIR_TBL_MAIN + (afterKeyFlag << 1))) || move((DIR_TBL_ID)(DIR_TBL_OPP + (afterKeyFlag << 1)))))
	//	{
	//		SetAnim("停止");
	//		return;
	//	}
	//}
	//else
	{
		afterKeyFlag = keyTbl[keyIdTbl[dirTbl[dir][DIR_TBL_SUB1]]] || keyTbl[keyIdTbl[dirTbl[dir][DIR_TBL_SUB2]]] ^ (int)(GetAnimation() == "停止");
	}
	SetAnim("移動");
	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
}

void Prey::Draw(void)
{
	//DrawBox(pos.x, pos.y, pos.x + GRIDSIZE, pos.y - (GRIDSIZE + 40), 0xff0000, true);
	Obj::Draw();
}

bool Prey::Init(void)
{
	AddAnim("停止", 0, 0, 2, 6);
	AddAnim("移動", 0, 2, 2, 6);
	return true;
}

#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



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
	Prey::Init();
	afterKeyFlag = false;
}


Prey::~Prey()
{
}

void Prey::Move(const Controller & controll, WeakList objlist)
{
	auto mapSize = lpMap.GetMapSize();
	auto gridSize = lpMap.GetGridSize().x;
	auto Scr = lpScene.GetScrSize();

	auto input = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto inputOld = controll.GetButtonInfo(KEY_TYPE_OLD);

	// 移動処理(Mapの移動 & ﾌﾟﾚｲﾔｰの移動)-----------------------------
	// 右移動
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (lpMap.GetMapPos().x > -11520)
		{
			camera.x = pos.x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
		}
	}
	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < 240)
		{
			camera.x = pos.x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < 240)
		{
			camera.y = pos.y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -8160)
		{
			camera.y = pos.y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
		}
	}
	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。
	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlag) {
		VECTOR2 side;
		switch (dir)
		{
		case DIR_LEFT:
			side = { speed - (sideFlag ^ 1), 0 };
			break;
		case DIR_RIGHT:
			side = { speed + (gridSize - sideFlag), 0 };
			break;
		case DIR_DOWN:
			side = { 0, speed + (gridSize - sideFlag) };
			break;
		case DIR_UP:
			side = { 0, speed - (sideFlag ^ 1) };
			break;
		}
		return pos + side;
	};

	auto move = [&, dir = Prey::dir](DIR_TBL_ID id){
		if (input[keyIdTbl[dirTbl[dir][id]]])
		{
			// 方向のｾｯﾄ
			Prey::dir = dirTbl[dir][id];
			if (!PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
			{
				// 移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合
				return false;
			}
			else
			{
				// 補正処理
				if ((*posTbl[Prey::dir][TBL_SUB]) % gridSize)
				{
					(*posTbl[Prey::dir][TBL_SUB]) = (((*posTbl[Prey::dir][TBL_SUB] + gridSize / 2) / gridSize) * gridSize);
				}
			}
			// 移動処理
			if (!(*posTbl[Prey::dir][TBL_SUB] % gridSize))
			{
				(*posTbl[Prey::dir][TBL_MAIN]) += speedTbl[Prey::dir];
				return true;
			}
		}
		return false;
	};

	if (!(move((DIR_TBL_ID)(DIR_TBL_SUB1 - (afterKeyFlag << 1)))
		|| move((DIR_TBL_ID)(DIR_TBL_SUB2 - (afterKeyFlag << 1)))))	// ｼﾌﾄ演算でafterKeyFlagを1ﾄﾞｯﾄずらす
	{
		afterKeyFlag = false;
		if (!(move((DIR_TBL_ID)(DIR_TBL_MAIN + (afterKeyFlag << 1))) || move((DIR_TBL_ID)(DIR_TBL_OPP + (afterKeyFlag << 1)))))
		{
			SetAnim("停止");
			return;
		}
	}
	else
	{
		afterKeyFlag = input[keyIdTbl[dirTbl[dir][DIR_TBL_SUB1]]] || input[keyIdTbl[dirTbl[dir][DIR_TBL_SUB2]]] ^ (int)(GetAnimation() == "停止");
	}
	SetAnim("移動");

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();
	//DrawRectGraph(camera.x + 320 - camera.x, camera.y + 280 - camera.y, 0, 0, 80, 120, lpImage.GetID("character/character.png")[0], true, false);
}

bool Prey::Init(void)
{
	Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	AddAnim("停止", 0, 0, 2, 6);
	AddAnim("移動", 0, 2, 2, 6);
	return true;
}

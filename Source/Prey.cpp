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
	//Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	Prey::Init();
	afterKeyFlag = false;
}


Prey::~Prey()
{
}

void Prey::Move(const Controller & controll, WeakList objlist)
{
	auto mapSize = lpMap.GetMapSize();
	auto gridSize = lpMap.GetGridSize();
	auto Scr = lpScene.GetScrSize();

	auto input = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto inputOld = controll.GetButtonInfo(KEY_TYPE_OLD);

	// 移動処理(Mapの移動 & ﾌﾟﾚｲﾔｰの移動)-----------------------------
	// 右移動
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		camera.x = pos.x += SPEED;
		lpMap.GetMapPos().x -= SPEED;
		/*if (pos.x >= 80)
		{
			if (pos.x < 320)
			{
				if (lpMap.GetMapPos().x >= 0)
				{
					pos.x += SPEED;
				}
			}
		}
		if (pos.x >= 320)
		{
			lpMap.GetMapPos().x -= SPEED;
		}*/
		/*if (pos.x >= Scr.x - PREYSIZE_X)
		{
			pos.x = Scr.x - PREYSIZE_X;
			lpMap.GetMapPos().x -= gridSize.x;
		}*/
		/*if (lpMap.GetMapPos().x <= -(mapSize.x - Scr.x))
		{
			lpMap.GetMapPos().x = -(mapSize.x - Scr.x);
			pos.x = Scr.x - (gridSize.x * 2);
		}*/
	}
	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		camera.x = pos.x -= SPEED;
		lpMap.GetMapPos().x += SPEED;
		/*if (pos.x > 80)
		{
			if (pos.x <= 320)
			{
				if (lpMap.GetMapPos().x >= 0)
				{
					pos.x -= SPEED;
				}
			}
		}
		if (pos.x >= 320)
		{
			lpMap.GetMapPos().x += SPEED;
		}*/
		/*if (pos.x <= 0)
		{
			pos.x = gridSize.x;
			lpMap.GetMapPos().x += gridSize.x;
		}
		if (lpMap.GetMapPos().x + mapSize.x >= mapSize.x - Scr.x)
		{
			lpMap.GetMapPos().x = 0;
		}*/
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		camera.y = pos.y -= SPEED;
		lpMap.GetMapPos().y += SPEED;
		/*if (pos.y > 40)
		{
			if (pos.y <= 280)
			{
				if (lpMap.GetMapPos().y >= 0)
				{
					pos.y -= SPEED;
				}
			}
		}
		if (pos.y >= 280)
		{
			lpMap.GetMapPos().y += SPEED;
		}*/
		/*if (pos.y <= 0)
		{
			pos.y = gridSize.y;
			lpMap.GetMapPos().y += gridSize.y;
		}
		if (lpMap.GetMapPos().y + lpMap.GetMapSize().y >= lpMap.GetMapSize().y - Scr.y)
		{
			lpMap.GetMapPos().y = 0;
		}*/
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		camera.y = pos.y += SPEED;
		lpMap.GetMapPos().y -= SPEED;
		/*if (pos.y >= 40)
		{
			if (pos.y < 280)
			{
				if (lpMap.GetMapPos().y >= 0)
				{
					pos.y += SPEED;
				}
			}
		}
		if (pos.y >= 280)
		{
			lpMap.GetMapPos().y -= SPEED;
		}*/
		/*if (pos.y >= Scr.y - gridSize.y)
		{
			pos.y = Scr.y - gridSize.y;
			lpMap.GetMapPos().y -= gridSize.y;
		}
		if (lpMap.GetMapPos().y <= -((lpMap.GetMapSize().y - Scr.y) + 20))
		{
			lpMap.GetMapPos().y = -((lpMap.GetMapSize().y - Scr.y) + 20);
			if (pos.y >= ((Scr.y - (GRIDSIZE * 2)) - 20))
			{
				pos.y = ((Scr.y - (GRIDSIZE * 2)) - 20);
			}
		}*/
	}
	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();
	DrawRectGraph(camera.x + 320 - camera.x, camera.y + 280 - camera.y, 0, 0, 80, 120, lpImage.GetID("character/character.png")[0], true, false);
}

bool Prey::Init(void)
{
	return true;
}

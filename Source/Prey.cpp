#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos,TYPE_NUM pNum,int num)
{
	this->typeObjNum = pNum;
	this->playerCnt = num;

	this->pos = pos;
	
	cameraPos = { 240,280 };

	individualsMapPos = lpMap.IndividualsMapCalcPos(pos,cameraPos,individualsMapPos);

	Prey::Init(pNum);

	dir = DIR_DOWN;
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

	//int keyList[PLAYER_MAX][DIR_MAX] = {
	//	{ KEY_INPUT_A,	// 左
	//	  KEY_INPUT_D,	// 右
	//	  KEY_INPUT_W,	// 上
	//	  KEY_INPUT_S	// 下
	//	},
	//	{ KEY_INPUT_NUMPAD4,	// 左
	//	  KEY_INPUT_NUMPAD6,	// 右
	//	  KEY_INPUT_NUMPAD8,	// 上
	//	  KEY_INPUT_NUMPAD2		// 下
	//	},
	//};

	// 移動処理(Mapの移動 & ﾌﾟﾚｲﾔｰの移動)-----------------------------
	// 右移動

	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (playerCnt == 1)
		{
			pos.x += SPEED;
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;

			if (pos.x >= MAPSIZE_X - GRIDSIZE)
			{
				pos.x = MAPSIZE_X - GRIDSIZE;
				//individualsMapPos.x = MAPSIZE_X - GRIDSIZE;
			}
			//individualsMapPos.x += GRIDSIZE;
			dir = DIR_RIGHT;
		}
	}

	// 右移動(2P)

	if (input[KEY_INPUT_RIGHT] & ~inputOld[KEY_INPUT_RIGHT])
	{
		if (individualsMapPos.x < (mapSize.x - GRIDSIZE * 5))
		{
			if (playerCnt == 2)
			{
				pos.x += SPEED;
				individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
				//individualsMapPos.x += GRIDSIZE;
				dir = DIR_RIGHT;
			}
		}
	}
	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (playerCnt == 1)
		{
			pos.x -= SPEED;
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
			if (pos.x <= GRIDSIZE)
			{
				pos.x = GRIDSIZE;
				individualsMapPos.x = -GRIDSIZE * 2;
			}
			dir = DIR_LEFT;
		}

	}
	// 左移動(2P)
	if (input[KEY_INPUT_LEFT] & ~inputOld[KEY_INPUT_LEFT])
	{
		if (individualsMapPos.x > -(GRIDSIZE * 2))
		{
			if (playerCnt == 2)
			{
				pos.x -= SPEED;
				individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
				//individualsMapPos.x -= GRIDSIZE;
				dir = DIR_LEFT;
			}
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (playerCnt == 1)
		{
			pos.y -= SPEED;
			individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
			if (pos.y <= GRIDSIZE - 40)
			{
				pos.y = GRIDSIZE - 40;
				individualsMapPos.y = -GRIDSIZE * 3;
			}
			dir = DIR_UP;
		}
	}
	// 上移動(2P)
	if (input[KEY_INPUT_UP] & ~inputOld[KEY_INPUT_UP])
	{
		if (individualsMapPos.y > -(GRIDSIZE * 3))
		{
			if (playerCnt == 2)
			{
				pos.y -= SPEED;
				
				individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
				//individualsMapPos.y -= GRIDSIZE;
				dir = DIR_UP;
			}
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (playerCnt == 1)
		{
			pos.y += SPEED;
			individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
			if (pos.y >= MAPSIZE_Y - ((GRIDSIZE * 2) + 40))
			{
				pos.y = MAPSIZE_Y - ((GRIDSIZE * 2) + 40);
				individualsMapPos.y = MAPSIZE_Y - (GRIDSIZE * 6);
			}
			dir = DIR_DOWN;
		}
	}
	// 下移動(2P)
	if (input[KEY_INPUT_DOWN] & ~inputOld[KEY_INPUT_DOWN])
	{
		if (individualsMapPos.y < mapSize.y - (GRIDSIZE * 6))
		{
			if (playerCnt == 2)
			{
				pos.y += SPEED;
				individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
				dir = DIR_DOWN;
			}
		}
	}
	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
}

void Prey::Draw(void)
{
	auto Scr = lpScene.GetScrSize();

	//Obj::Draw();
	
	DrawGraph((Scr.x / 2) * (playerCnt - 1) + cameraPos.x, cameraPos.y, lpImage.GetID("character/Prey.png")[typeObjNum * 2], true);



	DrawFormatString(130, 50 * playerCnt, 0xffffff, "pos%d:%d,%d\n",playerCnt, pos.x, pos.y);
	
	
	DrawFormatString(240, 50 * playerCnt, 0xffffff, "ind_map%d.x:%d\nind_map%d.y;%d", playerCnt,individualsMapPos.x,typeNum1, individualsMapPos.y);

}

bool Prey::Init(TYPE_NUM p_num)
{

	//lpMap.individualsMapPos[p_num] = { 0,0 };
	Obj::Init("character/Prey.png", VECTOR2(8, 4), VECTOR2(80, 120));

	return true;
}


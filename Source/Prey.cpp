#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos,TYPE_NUM pNum)
{
	this->typeNum = pNum;

	cameraPos = pos;
	/*mapPos = { 0,0 };
	individualsMapPos = { 0,0 };*/

	this->pos = pos;
	//lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos);

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
			if (mapPos.x > -(mapSize.x - GRIDSIZE * 5))
			{
				if (typeNum == PREY_1)
				{
					pos.x += SPEED;
					mapPos.x -= SPEED;
					individualsMapPos.x += GRIDSIZE;
					//lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;

					//lpMap.individualsMapPos[typeNum].x += GRIDSIZE;
					dir = DIR_RIGHT;
					//player[0].animation++;
				}
			}
		}

	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (mapPos.x < GRIDSIZE * 2)
		{
			if (typeNum == PREY_1)
			{
				pos.x -= SPEED;
				mapPos.x += SPEED;
				individualsMapPos.x -= GRIDSIZE;
				//lpMap.IndividualsMapCalcPos(pos, cameraPos,individualsMapPos).x;

				//lpMap.individualsMapPos[typeNum].x -= GRIDSIZE;
				dir = DIR_LEFT;
				//player[0].animation++;
			}
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (mapPos.y < GRIDSIZE * 3)
		{
			if (typeNum == PREY_1)
			{
				pos.y -= SPEED;
				mapPos.y += SPEED;
				individualsMapPos.y -= GRIDSIZE;
				//lpMap.IndividualsMapCalcPos(pos, cameraPos,individualsMapPos).y;

				//lpMap.individualsMapPos[typeNum].y -= GRIDSIZE;
				dir = DIR_UP;
			}
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (mapPos.y > -(mapSize.y - GRIDSIZE * 6))
		{
			if (typeNum == PREY_1)
			{
				pos.y += SPEED;
				mapPos.y -= SPEED;
				individualsMapPos.y += GRIDSIZE;
				//lpMap.IndividualsMapCalcPos(pos, cameraPos,individualsMapPos).y;

				//lpMap.individualsMapPos[typeNum].y += GRIDSIZE;
				dir = DIR_DOWN;
				//player[0].animation++;
			}
		}
	}

	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", mapPos.x,mapPos.y);
}

void Prey::Draw(void)
{
	auto Scr = lpScene.GetScrSize();
	//Obj::Draw();
	if (typeNum == PREY_1)
	{
		DrawGraph(cameraPos.x, cameraPos.y, lpImage.GetID("character/Prey.png")[0], true);
	}
	if (typeNum == PREY_2)
	{
		DrawGraph(cameraPos.x + (Scr.x / 2), cameraPos.y, lpImage.GetID("character/Prey.png")[4], true);
	}
	

	DrawFormatString(130, 50 * typeNum, 0xffffff, "pos%d:%d,%d\n",typeNum, pos.x, pos.y);
	
	
	DrawFormatString(0, 50 * typeNum, 0xffffff, "map.pos%d:%d,%d\n",typeNum,mapPos.x, mapPos.y);
	DrawFormatString(240, 50 * typeNum, 0xffffff, "ind_map%d.x:%d\nind_map%d.y;%d",typeNum,individualsMapPos.x,typeNum, individualsMapPos.y);

}

bool Prey::Init(TYPE_NUM p_num)
{

	//lpMap.individualsMapPos[p_num] = { 0,0 };
	Obj::Init("character/Prey.png", VECTOR2(8, 4), VECTOR2(80, 120));

	return true;
}

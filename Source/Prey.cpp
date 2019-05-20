#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2* pos, TYPE_NUM pNum)
{
	this->typeNum = pNum;

	/*this->pos[pNum].x = pos[pNum].x;
	this->pos[pNum].y = pos[pNum].y;*/

	SetPos(&pos[pNum]);
	Prey::Init(pNum);

	//pos[pNum] = this->player_cameraPos[pNum];
	dir[pNum] = DIR_DOWN;
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
		if (lpMap.GetMapPos().x > -(mapSize.x - GRIDSIZE * 5))
		{
			pos[typeNum].x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
			lpMap.GetIndividualsmapPos().x += SPEED;
			dir[typeNum] = DIR_RIGHT;
			//player[0].animation++;
		}
	}

	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < GRIDSIZE * 2)
		{
			pos[typeNum].x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
			lpMap.GetIndividualsmapPos().x -= SPEED;
			dir[typeNum] = DIR_LEFT;
			//player[0].animation++;
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < GRIDSIZE * 3)
		{
			pos[typeNum].y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
			lpMap.GetIndividualsmapPos().y -= GRIDSIZE;
			dir[typeNum] = DIR_UP;
			//player[0].animation++;
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -(mapSize.y - GRIDSIZE * 6))
		{
			pos[typeNum].y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
			lpMap.GetIndividualsmapPos().y += GRIDSIZE;
			dir[typeNum] = DIR_DOWN;
			//player[0].animation++;
		}
	}

	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", (&pos[typeNum].x), (&pos[typeNum].y));
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();

	//DrawGraph(GRIDSIZE * 3, GRIDSIZE * 4 - 40, charimage[PREY_1].image[0][0], true);
	//DrawGraph(GRIDSIZE * 3, GRIDSIZE * 4 - 40, charimage[PREY_2].image[0][0], true);

	//int animID = (player[0].animation / 1) % ANIMATION_MAX;

	if (typeNum == PREY_1)
	{
		DrawGraph(player_cameraPos[typeNum].x, player_cameraPos[typeNum].y, lpImage.GetID("character/character.png")[dir[typeNum]], true);
	}
	if (typeNum == PREY_2)
	{
		DrawGraph(player_cameraPos[typeNum].x, player_cameraPos[typeNum].y, lpImage.GetID("character/character2.png")[dir[typeNum]], true);
	}
	DrawFormatString(0, 0, 0xffffff, "character.pos:%d,%d\n", pos[typeNum].x, pos[typeNum].y);
	DrawFormatString(0, 20, 0xffffff, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool Prey::Init(TYPE_NUM p_num)
{

	if (p_num == PREY_1)
	{
		Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(80, 120));
	}
	if (p_num == PREY_2)
	{
		Obj::Init("character/character2.png", VECTOR2(4, 4), VECTOR2(80, 120));
	}
	player_cameraPos[typeNum] = { 240,280 };
	lpMap.IndividualsMapCalcPos(&pos[p_num], player_cameraPos[p_num]);

	return true;
}

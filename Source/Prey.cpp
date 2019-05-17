#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos, PREY_NUM p_num)
{
	Prey::Init(p_num);


	SetPos(player[0].pos[PREY_1]);
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].Flag = true;
		player[i].animation = 0;
	}
	//player[0].pos[PREY_1].x = GRIDSIZE * 3;
	//player[0].pos[PREY_1].y = GRIDSIZE * 4;
	player[0].dir = DIR_DOWN;
	player[1].dir = DIR_DOWN;
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
			player[0].pos[PREY_1].x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
			lpMap.individualsMapPos.x += SPEED;
			player[0].dir = DIR_RIGHT;
			player[0].animation++;
		}
	}

	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < GRIDSIZE * 2)
		{
			player[0].pos[PREY_1].x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
			lpMap.individualsMapPos.x -= SPEED;
			player[0].dir = DIR_LEFT;
			player[0].animation++;
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < GRIDSIZE * 3)
		{
			player[0].pos[PREY_1].y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
			lpMap.individualsMapPos.y -= GRIDSIZE;
			player[0].dir = DIR_UP;
			player[0].animation++;
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -(mapSize.y - GRIDSIZE * 6))
		{
			player[0].pos[PREY_1].y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
			lpMap.individualsMapPos.y += GRIDSIZE;
			player[0].dir = DIR_DOWN;
			player[0].animation++;
		}
	}

	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", player[0].pos[PREY_1].x, player[0].pos[PREY_1].y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();

	//DrawGraph(GRIDSIZE * 3, GRIDSIZE * 4 - 40, charimage[PREY_1].image[0][0], true);
	//DrawGraph(GRIDSIZE * 3, GRIDSIZE * 4 - 40, charimage[PREY_2].image[0][0], true);

	int animID = (player[0].animation / 1) % ANIMATION_MAX;

	DrawGraph(GRIDSIZE * 3, GRIDSIZE * 4 - 40, charimage[PREY_1].image[player[0].dir][animID], true);

	DrawFormatString(0, 0, 0xffffff, "character.pos:%d,%d\n", player[0].pos[PREY_1].x, player[0].pos[PREY_1].y);
	DrawFormatString(0, 20, 0xffffff, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool Prey::Init(PREY_NUM p_num)
{
	lpMap.IndividualsMapCalcPos(pos, player_cameraPos);

	const char *imageList[PREY_MAX] = {
		{"character/character.png" },
		{"character/character2.png"},
	};

	for (int i = 0; i < PREY_MAX; i++)
	{
		LoadDivGraph(imageList[i], DIR_MAX * ANIMATION_MAX, ANIMATION_MAX, DIR_MAX, PREYSIZE_X, PREYSIZE_Y, &charimage[i].image[0][0]);
	}

	return true;
}

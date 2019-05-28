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
	//dir = DIR_DOWN;
	AnimInit();
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
	// 右移動(1P)
	if (playerCnt == 1)
	{
		if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
		{
			// ｱﾆﾒｰｼｮﾝを開始
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			// dirを右方向に
			dir = DIR_RIGHT;
			SetAnim("move");
			// posの値のみの変化
			pos.x += SPEED;
			// ﾏｯﾌﾟ全体に対するｽｸﾘｰﾝのﾎﾟｼﾞｼｮﾝの変化
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
			// ﾏｯﾌﾟの右端に到達したら
			if (pos.x >= MAPSIZE_X - GRIDSIZE)
			{
				// 動かさない
				pos.x = MAPSIZE_X - GRIDSIZE;
				// 「止まる」ｱﾆﾒｰｼｮﾝの開始
				SetAnim("stop");
			}
		}
	}

	// 右移動(2P)
	if (playerCnt == 2)
	{
		if (input[KEY_INPUT_RIGHT] & ~inputOld[KEY_INPUT_RIGHT])
		{
			// 2Pのｱﾆﾒｰｼｮﾝを開始
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_RIGHT;
			SetAnim("move");
			pos.x += SPEED;
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
			if (pos.x >= MAPSIZE_X - GRIDSIZE)
			{
				pos.x = MAPSIZE_X - GRIDSIZE;
				SetAnim("stop");
			}
		}
	}
	// 左移動
	if (playerCnt == 1)
	{
		if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_LEFT;

			SetAnim("move");
			pos.x -= SPEED;
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
			if (pos.x <= GRIDSIZE)
			{
				pos.x = GRIDSIZE;
				individualsMapPos.x = -GRIDSIZE * 2;
				SetAnim("stop");
			}
		}
	}

	// 左移動(2P)
	if (playerCnt == 2)
	{
		if (input[KEY_INPUT_LEFT] & ~inputOld[KEY_INPUT_LEFT])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_LEFT;
			SetAnim("move");
			pos.x -= SPEED;
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
			if (pos.x <= GRIDSIZE)
			{
				pos.x = GRIDSIZE;
				individualsMapPos.x = -GRIDSIZE * 2;
				SetAnim("stop");
			}
		}
	}
	// 上移動
	if (playerCnt == 1)
	{
		if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_UP;

			SetAnim("move");
			pos.y -= SPEED;
			individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
			if (pos.y <= GRIDSIZE - 40)
			{
				pos.y = GRIDSIZE - 40;
				individualsMapPos.y = -GRIDSIZE * 3;
				SetAnim("stop");
			}
		}
	}

	// 上移動(2P)
	if (playerCnt == 2)
	{
		if (input[KEY_INPUT_UP] & ~inputOld[KEY_INPUT_UP])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_UP;
			SetAnim("move");
			pos.y -= SPEED;
			individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
			if (pos.y <= GRIDSIZE - 40)
			{
				pos.y = GRIDSIZE - 40;
				individualsMapPos.y = -GRIDSIZE * 3;
				SetAnim("stop");
			}
		}
	}
	// 下移動
	if (playerCnt == 1)
	{
		if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_DOWN;

			SetAnim("move");
			pos.y += SPEED;
			individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
			if (pos.y >= MAPSIZE_Y - ((GRIDSIZE * 2) + 40))
			{
				pos.y = MAPSIZE_Y - ((GRIDSIZE * 2) + 40);
				individualsMapPos.y = MAPSIZE_Y - (GRIDSIZE * 6);
				SetAnim("stop");
			}
		}
	}
	// 下移動(2P)
	if (playerCnt == 2)
	{
		if (input[KEY_INPUT_DOWN] & ~inputOld[KEY_INPUT_DOWN])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_DOWN;
			SetAnim("move");
			pos.y += SPEED;
			individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).y;
			if (pos.y >= MAPSIZE_Y - ((GRIDSIZE * 2) + 40))
			{
				pos.y = MAPSIZE_Y - ((GRIDSIZE * 2) + 40);
				individualsMapPos.y = MAPSIZE_Y - (GRIDSIZE * 6);
				SetAnim("stop");
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
	Obj::Draw();
	
	// 1P 2P のposの表示(ﾃﾞﾊﾞｯｸﾞ用)
	DrawFormatString(130, 50 * playerCnt, 0xffffff, "pos%d:%d,%d\n",playerCnt, pos.x, pos.y);
	
	// 1P 2P のindividualsMapPosの表示(ﾃﾞﾊﾞｯｸﾞ用)
	DrawFormatString(240, 50 * playerCnt, 0xffffff, "ind_map%d.x:%d\nind_map%d.y;%d", playerCnt,individualsMapPos.x,typeNum1, individualsMapPos.y);

	// 1P 2P のtypeNumの表示(ﾃﾞﾊﾞｯｸﾞ用)
	DrawFormatString(400, 50 * playerCnt, 0xffffff, "typeNum:%d\n",typeObjNum);
	// 1P 2P のdirの表示(ﾃﾞﾊﾞｯｸﾞ用)
	DrawFormatString(400, 150 * playerCnt, 0xffffff, "dir:%d", dir);
}

bool Prey::Init(TYPE_NUM p_num)
{
	// 1P 2P 3P の操作しているｷｬﾗ毎の画像読み込み
	if (p_num == PREY_1)
	{
		Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(GRIDSIZE, GRIDSIZE + 40));
	}
	if (p_num == PREY_2)
	{
		Obj::Init("character/character2.png", VECTOR2(4, 4), VECTOR2(GRIDSIZE, GRIDSIZE + 40));
	}
	if (p_num == PREY_3)
	{
		Obj::Init("character/character2.png", VECTOR2(4, 4), VECTOR2(GRIDSIZE, GRIDSIZE + 40));
	}

	return true;
}

bool Prey::AnimInit(void)
{
	// 前後左右に歩くｱﾆﾒｰｼｮﾝ
	AddAnim("move",3, 6);
	// 壁に当たったら立ち止まるｱﾆﾒｰｼｮﾝ
	AddAnim("stop",1, 1);
	return true;
}


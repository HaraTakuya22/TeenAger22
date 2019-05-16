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
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	//			MAIN	
	posTbl = {	&pos.y,	&pos.x,	// 下
				&pos.x,	&pos.y, // 左
				&pos.x,	&pos.y, // 右
				&pos.y,	&pos.x, // 上
	};

	//lpMap.GetMapPos() = { -640,-640 };
	//			MAIN			
	keyIdTbl = { KEY_INPUT_NUMPAD2,	// 下
				 KEY_INPUT_NUMPAD4,	// 左
				 KEY_INPUT_NUMPAD6,	// 右
				 KEY_INPUT_NUMPAD8,	// 上
	};
	//			MAIN		OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,	DIR_UP,		DIR_LEFT,	DIR_RIGHT,	// 下（上・左・右）
				DIR_LEFT,	DIR_RIGHT,	DIR_DOWN,	DIR_UP,		// 左（右・下・上）
				DIR_RIGHT,	DIR_LEFT,	DIR_DOWN,	DIR_UP,		// 右（左・下・上）
				DIR_UP,		DIR_DOWN,	DIR_LEFT,	DIR_RIGHT,	// 上（下・左・右）
	};

	idTbl = {
	true,		//FLOOR			// 床
	false,		//WALL			// 壁
	false,		//CHAIR_1		// 椅子1
	false,		//CHAIR_2		// 椅子2
	false,		//CHAIR_3		// 椅子3
	false,		//CHAIR_4		// 椅子4
	false,		//BOOKSHELF		// 本棚
	false,		//DRAWER		// 引き出し
	false,		//LOCKER		// ﾛｯｶｰ
	false,		//VASE_1		// 花瓶1
	false,		//VASE_2		// 花瓶2
	false,		//MIRRORTABLE	// 鏡台
	false,		//FACE			// 洗面台
	false,		//KITCHIN_1		// 台所1
	false,		//KITCHIN_2		// 台所2
	false,		//S_MONITOR		// 小さいﾓﾆﾀｰ
	false,		//BED			// ﾍﾞｯﾄﾞ
	false,		//DESK			// 横に長い机
	false,		//MONITOR		// 大きいﾓﾆﾀｰ
	false,		//S_TABLE		// 縦に長い机1
	false,		//TABLE			// 縦に長い机2
	true,		//NON			// 何もない
	};

	// player(鬼以外)のﾎﾟｼﾞｼｮﾝのｾｯﾄ
	SetPos(pos);
	Prey::Init(p_num);
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

	auto sidePos = [&](DIR dir, VECTOR2 pos, SIDE_CHECK sideflag) {
		VECTOR2 side;
		switch (dir)
		{
		case DIR_LEFT:
			side = { (sideflag - gridSize), 0 };
		case DIR_RIGHT:
			side = { sideflag, 0 };
		case DIR_DOWN:
			side = { 0, sideflag };
		case DIR_UP:
			side = { 0,(sideflag - gridSize) };
			break;
		}
		return pos + side;
	};

	// 移動処理(Mapの移動 & ﾌﾟﾚｲﾔｰの移動)-----------------------------
	// 右移動
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (lpMap.GetMapPos().x > -11520)
		{
			pos.x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
			lpMap.individualsMapPos.x += GRIDSIZE;
		}
	}

	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < 240)
		{
			pos.x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
			lpMap.individualsMapPos.x -= GRIDSIZE;
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < 240)
		{
			pos.y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
			lpMap.individualsMapPos.y -= GRIDSIZE;
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -8160)
		{
			pos.y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
			lpMap.individualsMapPos.y += GRIDSIZE;
		}
	}


	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。
	
	auto move = [&, dir = Prey::dir](DIR_TBL_ID id){
		if (input[keyIdTbl[dirTbl[dir][id]]])
		{
			// 方向のｾｯﾄ
			Prey::dir = dirTbl[dir][id];
			if (!idTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, IN_SIDE)))])
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
				(*posTbl[Prey::dir][TBL_MAIN]) += SPEED;
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
	
	DrawFormatString(0, 0, 0xffffff, "character.pos:%d,%d\n",pos.x, pos.y);
	DrawFormatString(0, 20, 0xffffff, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool Prey::Init(PREY_NUM p_num)
{
	if (p_num == PREY_1)
	{
		Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	}
	if (p_num == PREY_2)
	{
		Obj::Init("character/character2.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	}
	
	lpMap.IndividualsMapCalcPos(pos, player_cameraPos);

	AddAnim("停止", 0, 0, 2, 6);
	AddAnim("移動", 0, 2, 2, 6);
	return true;
}

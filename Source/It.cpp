#include <DxLib.h>
#include "Scene.h"
#include "It.h"
#include "Controller.h"
#include "Image.h"


It::It()
{
}

It::It(VECTOR2 pos)
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
	speedTbl = { IT_DEF_SPEED,	// 下
				 -IT_DEF_SPEED,	// 左
				 IT_DEF_SPEED,	// 右
				 -IT_DEF_SPEED,	// 上
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

	// 鬼のﾎﾟｼﾞｼｮﾝのｾｯﾄ
	SetPos(pos);
	It::Init();
	afterKeyFlag = false;
	// 鬼のﾎﾟｼﾞｼｮﾝのｾｯﾄ
	SetPos(pos);

	itflag = true;
}


It::~It()
{
}

void It::Draw(void)
{
	Obj::Draw();
	DrawFormatString(0, 0, 0xffffff, "character.pos:%d,%d\n", pos.x, pos.y);
	DrawFormatString(0, 20, 0xffffff, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);

}

void It::Move(const Controller & controll, WeakList objlist)
{
	auto mapSize = lpMap.GetMapSize();
	auto gridSize = lpMap.GetGridSize().x;
	auto Scr = lpScene.GetScrSize();
	//auto camera = lpMap.GetCamera();

	auto input = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto inputOld = controll.GetButtonInfo(KEY_TYPE_OLD);

	// 移動処理(Mapの移動 & ﾌﾟﾚｲﾔｰの移動)-----------------------------
	// 右移動
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (lpMap.GetMapPos().x > -11520)
		{
			pos.x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
		}
	}
	// 左移動
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < 240)
		{
			pos.x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
		}
	}
	// 上移動
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < 240)
		{
			pos.y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
		}
	}
	// 下移動
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -8160)
		{
			pos.y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
		}
	}
	//----------------------------------------------------------------------------

	// ＊ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝを足元に設定する。
	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, IT_SIDE_CHECK sideFlag) {
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

	auto move = [&, dir = It::dir](IT_DIR_TBL_ID id){
		if (input[keyIdTbl[dirTbl[dir][id]]])
		{
			// 方向のｾｯﾄ
			It::dir = dirTbl[dir][id];
			if (!PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(It::dir, pos, speedTbl[It::dir], IT_IN_SIDE)))])
			{
				// 移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合
				return false;
			}
			else
			{
				// 補正処理
				if ((*posTbl[It::dir][IT_TBL_SUB]) % gridSize)
				{
					//(*posTbl[Prey::dir][TBL_SUB]) = (((*posTbl[Prey::dir][TBL_SUB] + gridSize / 2) / gridSize) * gridSize);
				}
			}
			// 移動処理
			if (!(*posTbl[It::dir][IT_TBL_SUB] % gridSize))
			{
				(*posTbl[It::dir][IT_TBL_MAIN]) += speedTbl[It::dir];
				return true;
			}
		}
		return false;
	};

	if (!(move((IT_DIR_TBL_ID)(IT_DIR_TBL_SUB1 - (afterKeyFlag << 1)))
		|| move((IT_DIR_TBL_ID)(IT_DIR_TBL_SUB2 - (afterKeyFlag << 1)))))	// ｼﾌﾄ演算でafterKeyFlagを1ﾄﾞｯﾄずらす
	{
		afterKeyFlag = false;
		if (!(move((IT_DIR_TBL_ID)(IT_DIR_TBL_MAIN + (afterKeyFlag << 1))) || move((IT_DIR_TBL_ID)(IT_DIR_TBL_OPP + (afterKeyFlag << 1)))))
		{
			SetAnim("停止");
			return;
		}
	}
	else
	{
		afterKeyFlag = input[keyIdTbl[dirTbl[dir][IT_DIR_TBL_SUB1]]] || input[keyIdTbl[dirTbl[dir][IT_DIR_TBL_SUB2]]] ^ (int)(GetAnimation() == "停止");
	}
	SetAnim("移動");

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool It::Init(void)
{
	Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	AddAnim("停止", 0, 0, 2, 6);
	AddAnim("移動", 0, 2, 2, 6);
	return true;
}

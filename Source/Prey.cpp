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
	keyIdTbl = { KEY_INPUT_NUMPAD2,	// ��
				 KEY_INPUT_NUMPAD4,	// ��
				 KEY_INPUT_NUMPAD6,	// �E
				 KEY_INPUT_NUMPAD8,	// ��
	};
	//			MAIN	
	posTbl = { &pos.y, &pos.x,	// ��
				&pos.x,	&pos.y, // ��
				&pos.x,	&pos.y, // �E
				&pos.y,	&pos.x, // ��
	};
	//			MAIN
	speedTbl = { PLAYER_DEF_SPEED,	// ��
				 -PLAYER_DEF_SPEED,	// ��
				 PLAYER_DEF_SPEED,	// �E
				 -PLAYER_DEF_SPEED,	// ��
	};
	//			MAIN		OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,	DIR_UP,		DIR_LEFT,	DIR_RIGHT,	// ���i��E���E�E�j
				DIR_LEFT,	DIR_RIGHT,	DIR_DOWN,	DIR_UP,		// ���i�E�E���E��j
				DIR_RIGHT,	DIR_LEFT,	DIR_DOWN,	DIR_UP,		// �E�i���E���E��j
				DIR_UP,		DIR_DOWN,	DIR_LEFT,	DIR_RIGHT,	// ��i���E���E�E�j
	};

	PassageTbl = {
		true,	//PASSAGE_WAY
		false,	//PASSAGE_WALL
	};

	// player(�S�ȊO)���߼޼�݂̾��
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
			// �����̾��
			Prey::dir = dirTbl[dir][id];
			if (!PassageTbl[static_cast<int>(lpMap.GetMapData(SidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
			{
				// �ǂ��ׂɂ������ꍇ
				return false;
			}
			else
			{
				// �␳����
				if ((*posTbl[Prey::dir][TBL_SUB]) % GRIDSIZE)
				{
					(*posTbl[Prey::dir][TBL_SUB]) = (((*posTbl[Prey::dir][TBL_SUB] + GRIDSIZE / 2) / GRIDSIZE) * GRIDSIZE);
				}
			}
			// �ړ�����
			if (!(*posTbl[Prey::dir][TBL_SUB] % GRIDSIZE))
			{
				(*posTbl[Prey::dir][TBL_MAIN]) += speedTbl[Prey::dir];
				return true;
			}
		}
		return false;
	};

	//if (!(move((DIR_TBL_ID)(DIR_TBL_SUB1 - (afterKeyFlag << 1)))
	//	|| move((DIR_TBL_ID)(DIR_TBL_SUB2 - (afterKeyFlag << 1)))))	// ��ĉ��Z��afterKeyFlag��1�ޯĂ��炷
	//{
	//	afterKeyFlag = false;
	//	if (!(move((DIR_TBL_ID)(DIR_TBL_MAIN + (afterKeyFlag << 1))) || move((DIR_TBL_ID)(DIR_TBL_OPP + (afterKeyFlag << 1)))))
	//	{
	//		SetAnim("��~");
	//		return;
	//	}
	//}
	//else
	{
		afterKeyFlag = keyTbl[keyIdTbl[dirTbl[dir][DIR_TBL_SUB1]]] || keyTbl[keyIdTbl[dirTbl[dir][DIR_TBL_SUB2]]] ^ (int)(GetAnimation() == "��~");
	}
	SetAnim("�ړ�");
	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
}

void Prey::Draw(void)
{
	//DrawBox(pos.x, pos.y, pos.x + GRIDSIZE, pos.y - (GRIDSIZE + 40), 0xff0000, true);
	Obj::Draw();
}

bool Prey::Init(void)
{
	AddAnim("��~", 0, 0, 2, 6);
	AddAnim("�ړ�", 0, 2, 2, 6);
	return true;
}

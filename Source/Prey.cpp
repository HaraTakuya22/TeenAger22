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
	true,		//FLOOR			// ��
	false,		//WALL			// ��
	false,		//CHAIR_1		// �֎q1
	false,		//CHAIR_2		// �֎q2
	false,		//CHAIR_3		// �֎q3
	false,		//CHAIR_4		// �֎q4
	false,		//BOOKSHELF		// �{�I
	false,		//DRAWER		// �����o��
	false,		//LOCKER		// ۯ��
	false,		//VASE_1		// �ԕr1
	false,		//VASE_2		// �ԕr2
	false,		//MIRRORTABLE	// ����
	false,		//FACE			// ���ʑ�
	false,		//KITCHIN_1		// �䏊1
	false,		//KITCHIN_2		// �䏊2
	false,		//S_MONITOR		// ����������
	false,		//BED			// �ޯ��
	false,		//DESK			// ���ɒ�����
	false,		//MONITOR		// �傫������
	false,		//S_TABLE		// �c�ɒ�����1
	false,		//TABLE			// �c�ɒ�����2
	true,		//NON			// �����Ȃ�
	};

	// player(�S�ȊO)���߼޼�݂̾��
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

	// �ړ�����(Map�̈ړ� & ��ڲ԰�̈ړ�)-----------------------------
	// �E�ړ�
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
		{
			if (lpMap.GetMapPos().x > -11520)
			{
				pos.x += SPEED;
				lpMap.GetMapPos().x -= SPEED;
			}
		}
	}
	// ���ړ�
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
		{
			if (lpMap.GetMapPos().x < 240)
			{
				pos.x -= SPEED;
				lpMap.GetMapPos().x += SPEED;
			}
		}
	}
	// ��ړ�
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
		{
			if (lpMap.GetMapPos().y < 240)
			{
				pos.y -= SPEED;
				lpMap.GetMapPos().y += SPEED;
			}
		}
	}
	// ���ړ�
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
		{
			if (lpMap.GetMapPos().y > -8160)
			{
				pos.y += SPEED;
				lpMap.GetMapPos().y -= SPEED;
			}
		}
	}
	//----------------------------------------------------------------------------

	// ����ڲ԰���߼޼�݂𑫌��ɐݒ肷��B
	
	auto move = [&, dir = Prey::dir](DIR_TBL_ID id){
		if (input[keyIdTbl[dirTbl[dir][id]]])
		{
			// �����̾��
			Prey::dir = dirTbl[dir][id];
			if (!PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(Prey::dir, pos, speedTbl[Prey::dir], IN_SIDE)))])
			{
				// �ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ
				return false;
			}
			else
			{
				// �␳����
				if ((*posTbl[Prey::dir][TBL_SUB]) % gridSize)
				{
					(*posTbl[Prey::dir][TBL_SUB]) = (((*posTbl[Prey::dir][TBL_SUB] + gridSize / 2) / gridSize) * gridSize);
				}
			}
			// �ړ�����
			if (!(*posTbl[Prey::dir][TBL_SUB] % gridSize))
			{
				(*posTbl[Prey::dir][TBL_MAIN]) += speedTbl[Prey::dir];
				return true;
			}
		}
		return false;
	};

	if (!(move((DIR_TBL_ID)(DIR_TBL_SUB1 - (afterKeyFlag << 1)))
		|| move((DIR_TBL_ID)(DIR_TBL_SUB2 - (afterKeyFlag << 1)))))	// ��ĉ��Z��afterKeyFlag��1�ޯĂ��炷
	{
		afterKeyFlag = false;
		if (!(move((DIR_TBL_ID)(DIR_TBL_MAIN + (afterKeyFlag << 1))) || move((DIR_TBL_ID)(DIR_TBL_OPP + (afterKeyFlag << 1)))))
		{
			SetAnim("��~");
			return;
		}
	}
	else
	{
		afterKeyFlag = input[keyIdTbl[dirTbl[dir][DIR_TBL_SUB1]]] || input[keyIdTbl[dirTbl[dir][DIR_TBL_SUB2]]] ^ (int)(GetAnimation() == "��~");
	}
	SetAnim("�ړ�");

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();
	DrawFormatString(0, 0, 0xffffff, "character.pos:%d,%d\n", pos.x, pos.y);
	DrawFormatString(0, 20, 0xffffff, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool Prey::Init(void)
{
	Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	AddAnim("��~", 0, 0, 2, 6);
	AddAnim("�ړ�", 0, 2, 2, 6);
	return true;
}

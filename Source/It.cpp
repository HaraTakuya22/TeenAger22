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
	speedTbl = { IT_DEF_SPEED,	// ��
				 -IT_DEF_SPEED,	// ��
				 IT_DEF_SPEED,	// �E
				 -IT_DEF_SPEED,	// ��
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

	// �S���߼޼�݂̾��
	SetPos(pos);
	It::Init();
	afterKeyFlag = false;
	// �S���߼޼�݂̾��
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

	// �ړ�����(Map�̈ړ� & ��ڲ԰�̈ړ�)-----------------------------
	// �E�ړ�
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (lpMap.GetMapPos().x > -11520)
		{
			pos.x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
		}
	}
	// ���ړ�
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < 240)
		{
			pos.x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
		}
	}
	// ��ړ�
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < 240)
		{
			pos.y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
		}
	}
	// ���ړ�
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -8160)
		{
			pos.y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
		}
	}
	//----------------------------------------------------------------------------

	// ����ڲ԰���߼޼�݂𑫌��ɐݒ肷��B
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
			// �����̾��
			It::dir = dirTbl[dir][id];
			if (!PassageTbl[static_cast<int>(lpMap.GetMapData(sidePos(It::dir, pos, speedTbl[It::dir], IT_IN_SIDE)))])
			{
				// �ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ
				return false;
			}
			else
			{
				// �␳����
				if ((*posTbl[It::dir][IT_TBL_SUB]) % gridSize)
				{
					//(*posTbl[Prey::dir][TBL_SUB]) = (((*posTbl[Prey::dir][TBL_SUB] + gridSize / 2) / gridSize) * gridSize);
				}
			}
			// �ړ�����
			if (!(*posTbl[It::dir][IT_TBL_SUB] % gridSize))
			{
				(*posTbl[It::dir][IT_TBL_MAIN]) += speedTbl[It::dir];
				return true;
			}
		}
		return false;
	};

	if (!(move((IT_DIR_TBL_ID)(IT_DIR_TBL_SUB1 - (afterKeyFlag << 1)))
		|| move((IT_DIR_TBL_ID)(IT_DIR_TBL_SUB2 - (afterKeyFlag << 1)))))	// ��ĉ��Z��afterKeyFlag��1�ޯĂ��炷
	{
		afterKeyFlag = false;
		if (!(move((IT_DIR_TBL_ID)(IT_DIR_TBL_MAIN + (afterKeyFlag << 1))) || move((IT_DIR_TBL_ID)(IT_DIR_TBL_OPP + (afterKeyFlag << 1)))))
		{
			SetAnim("��~");
			return;
		}
	}
	else
	{
		afterKeyFlag = input[keyIdTbl[dirTbl[dir][IT_DIR_TBL_SUB1]]] || input[keyIdTbl[dirTbl[dir][IT_DIR_TBL_SUB2]]] ^ (int)(GetAnimation() == "��~");
	}
	SetAnim("�ړ�");

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool It::Init(void)
{
	Obj::Init("character/character.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	AddAnim("��~", 0, 0, 2, 6);
	AddAnim("�ړ�", 0, 2, 2, 6);
	return true;
}

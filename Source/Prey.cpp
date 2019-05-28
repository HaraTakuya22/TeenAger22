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

	// �ړ�����(Map�̈ړ� & ��ڲ԰�̈ړ�)-----------------------------
	// �E�ړ�(1P)
	if (playerCnt == 1)
	{
		if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
		{
			// ��Ұ��݂��J�n
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			// dir���E������
			dir = DIR_RIGHT;
			SetAnim("move");
			// pos�̒l�݂̂̕ω�
			pos.x += SPEED;
			// ϯ�ߑS�̂ɑ΂��齸ذ݂��߼޼�݂̕ω�
			individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, cameraPos, individualsMapPos).x;
			// ϯ�߂̉E�[�ɓ��B������
			if (pos.x >= MAPSIZE_X - GRIDSIZE)
			{
				// �������Ȃ�
				pos.x = MAPSIZE_X - GRIDSIZE;
				// �u�~�܂�v��Ұ��݂̊J�n
				SetAnim("stop");
			}
		}
	}

	// �E�ړ�(2P)
	if (playerCnt == 2)
	{
		if (input[KEY_INPUT_RIGHT] & ~inputOld[KEY_INPUT_RIGHT])
		{
			// 2P�̱�Ұ��݂��J�n
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
	// ���ړ�
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

	// ���ړ�(2P)
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
	// ��ړ�
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

	// ��ړ�(2P)
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
	// ���ړ�
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
	// ���ړ�(2P)
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

	// ����ڲ԰���߼޼�݂𑫌��ɐݒ肷��B

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos.x, pos.y);
}

void Prey::Draw(void)
{
	auto Scr = lpScene.GetScrSize();
	Obj::Draw();
	
	// 1P 2P ��pos�̕\��(���ޯ�ޗp)
	DrawFormatString(130, 50 * playerCnt, 0xffffff, "pos%d:%d,%d\n",playerCnt, pos.x, pos.y);
	
	// 1P 2P ��individualsMapPos�̕\��(���ޯ�ޗp)
	DrawFormatString(240, 50 * playerCnt, 0xffffff, "ind_map%d.x:%d\nind_map%d.y;%d", playerCnt,individualsMapPos.x,typeNum1, individualsMapPos.y);

	// 1P 2P ��typeNum�̕\��(���ޯ�ޗp)
	DrawFormatString(400, 50 * playerCnt, 0xffffff, "typeNum:%d\n",typeObjNum);
	// 1P 2P ��dir�̕\��(���ޯ�ޗp)
	DrawFormatString(400, 150 * playerCnt, 0xffffff, "dir:%d", dir);
}

bool Prey::Init(TYPE_NUM p_num)
{
	// 1P 2P 3P �̑��삵�Ă��鷬ז��̉摜�ǂݍ���
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
	// �O�㍶�E�ɕ�����Ұ���
	AddAnim("move",3, 6);
	// �ǂɓ��������痧���~�܂��Ұ���
	AddAnim("stop",1, 1);
	return true;
}


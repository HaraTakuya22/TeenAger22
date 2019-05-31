#include <DxLib.h>

#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos,TYPE_NUM pNum,PLAYER num,VECTOR2 camera)
{
	this->typeObjNum = pNum;

	player = num;

	this->pos = pos;
	this->cameraPosition = camera;
	fixedPos = { 240,280 };	

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

	auto cnt_now = controll.GetButtonInfo()[KEY_TYPE_NOW];
	auto cnt_old = controll.GetButtonInfo()[KEY_TYPE_OLD];

	auto key_now = controll.GetKeyButtonInfo(KEY_TYPE_NOW);
	auto key_old = controll.GetKeyButtonInfo(KEY_TYPE_OLD);

	//pos = lpCamera.GetCamera();

	// �ړ�����(Map�̈ړ� & ��ڲ԰�̈ړ�)-----------------------------
	// �E�ړ�(1P)
	if (player == PLAYER::PLAYER_1)
	{
		if (key_now[KEY_INPUT_RIGHT] & ~key_old[KEY_INPUT_RIGHT])
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
			pos.x += GRIDSIZE;
			cameraPosition.x += GRIDSIZE;
			// ϯ�ߑS�̂ɑ΂��齸ذ݂��߼޼�݂̕ω�
			//individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, objCameraPos,individualsMapPos).x;
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
	if (player == PLAYER::PLAYER_2)
	{
		if (key_now[KEY_INPUT_NUMPAD6] & ~key_old[KEY_INPUT_NUMPAD6])
		{
			// 2P�̱�Ұ��݂��J�n
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_RIGHT;
			SetAnim("move");
			pos.x += GRIDSIZE;
			//individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, objCameraPos,individualsMapPos).x;
			if (pos.x >= MAPSIZE_X - GRIDSIZE)
			{
				pos.x = MAPSIZE_X - GRIDSIZE;
				SetAnim("stop");
			}
		}
	}
	// ���ړ�
	if (player == PLAYER::PLAYER_1)
	{
		if (key_now[KEY_INPUT_LEFT] & ~key_old[KEY_INPUT_LEFT])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_LEFT;

			SetAnim("move");
			pos.x -= GRIDSIZE;
			//individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, objCameraPos, individualsMapPos).x;
			if (pos.x <= GRIDSIZE)
			{
				pos.x = GRIDSIZE;
				//individualsMapPos.x = -GRIDSIZE * 2;
				SetAnim("stop");
			}
		}
	}

	// ���ړ�(2P)
	if (player == PLAYER::PLAYER_2)
	{
		if (key_now[KEY_INPUT_NUMPAD4] & ~key_old[KEY_INPUT_NUMPAD4])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_LEFT;
			SetAnim("move");
			pos.x -= GRIDSIZE;
			//individualsMapPos.x = lpMap.IndividualsMapCalcPos(pos, objCameraPos, individualsMapPos).x;
			if (pos.x <= GRIDSIZE)
			{
				pos.x = GRIDSIZE;
				//individualsMapPos.x = -GRIDSIZE * 2;
				SetAnim("stop");
			}
		}
	}
	// ��ړ�
	if (player == PLAYER::PLAYER_1)
	{
		if (key_now[KEY_INPUT_UP] & ~key_old[KEY_INPUT_UP])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_UP;

			SetAnim("move");
			pos.y -= GRIDSIZE;
			//individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, objCameraPos, individualsMapPos).y;
			if (pos.y <= GRIDSIZE - 40)
			{
				pos.y = GRIDSIZE - 40;
				//individualsMapPos.y = -GRIDSIZE * 3;
				SetAnim("stop");
			}
		}
	}

	// ��ړ�(2P)
	if (player == PLAYER::PLAYER_2)
	{
		if (key_now[KEY_INPUT_NUMPAD8] & ~key_old[KEY_INPUT_NUMPAD8])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_UP;
			SetAnim("move");
			pos.y -= GRIDSIZE;
			//individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, objCameraPos, individualsMapPos).y;
			if (pos.y <= GRIDSIZE - 40)
			{
				pos.y = GRIDSIZE - 40;
				//individualsMapPos.y = -GRIDSIZE * 3;
				SetAnim("stop");
			}
		}
	}
	// ���ړ�
	if (player == PLAYER::PLAYER_1)
	{
		if (key_now[KEY_INPUT_DOWN] & ~key_old[KEY_INPUT_DOWN])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_DOWN;

			SetAnim("move");
			pos.y += GRIDSIZE;
			//individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, objCameraPos, individualsMapPos).y;
			if (pos.y >= MAPSIZE_Y - ((GRIDSIZE * 2) + 40))
			{
				pos.y = MAPSIZE_Y - ((GRIDSIZE * 2) + 40);
				//individualsMapPos.y = MAPSIZE_Y - (GRIDSIZE * 6);
				SetAnim("stop");
			}
		}
	}
	// ���ړ�(2P)
	if (player == PLAYER::PLAYER_2)
	{
		if (key_now[KEY_INPUT_NUMPAD2] & ~key_old[KEY_INPUT_NUMPAD2])
		{
			AniCnt++;
			if (AniCnt >= 4)
			{
				AniCnt = 0;
			}
			dir = DIR_DOWN;
			SetAnim("move");
			pos.y += GRIDSIZE;
			//individualsMapPos.y = lpMap.IndividualsMapCalcPos(pos, objCameraPos, individualsMapPos).y;
			if (pos.y >= MAPSIZE_Y - ((GRIDSIZE * 2) + 40))
			{
				pos.y = MAPSIZE_Y - ((GRIDSIZE * 2) + 40);
				//individualsMapPos.y = MAPSIZE_Y - (GRIDSIZE * 6);
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
	DrawFormatString(130, 50 * (int)player, 0xffffff, "pos%d:%d,%d\n",player, pos.x, pos.y);
	
	// 1P 2P ��individualsMapPos�̕\��(���ޯ�ޗp)
	DrawFormatString(240, 50 * (int)player, 0xffffff, "camera_pos%d.x:%d\ncamera_pos%d.y;%d",cameraPosition.x,player, cameraPosition.y);

	// 1P 2P ��typeNum�̕\��(���ޯ�ޗp)
	DrawFormatString(400, 50 * (int)player, 0xffffff, "typeNum:%d\n",typeObjNum);
	// 1P 2P ��dir�̕\��(���ޯ�ޗp)
	DrawFormatString(400, 150 * (int)player, 0xffffff, "dir:%d", dir);
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
		Obj::Init("character/character3.png", VECTOR2(4, 4), VECTOR2(GRIDSIZE, GRIDSIZE + 40));
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


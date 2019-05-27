#include <DxLib.h>
#include "Scene.h"
#include "Map.h"
#include "Image.h"
#include "EditCursor.h"


#define EDITCURSOR_DEF_RNG	(30)
#define EDITCURSOR_MIN_RNG	(5)

EditCursor::EditCursor(VECTOR2 pos,TYPE_NUM num)
{
	//playerCnt = 0;
	typeCursor = num;

 	this->pos.x = pos.x;
	this->pos.y = pos.y;

	cameraPos = { 320,320 };
	//mapPos = { 0,0 };
	individualsMapPos = { 0,0 };

	keyDefRng = EDITCURSOR_DEF_RNG;
	inputFrame = EDITCURSOR_DEF_RNG;
	setF = false;
}


EditCursor::~EditCursor()
{
}

void EditCursor::Move(const Controller & controll, WeakList objlist)
{
	InputOld[dir] = InputNow[dir];
	ChangeInputOld = ChangeInput;
	ChangeInputBackOld = ChangeInputBack;
	SetInputOld = SetInput;
	VECTOR2 tmp(pos);
	//VECTOR2 tmpMappos(mapPos);

	// �ް��߯�ނ̓���
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	auto cnt_now = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto cnt_old = controll.GetButtonInfo(KEY_TYPE_OLD);

	auto Scr = lpScene.GetScrSize();
	auto gridSize = lpMap.GetGridSize();



	// �������u�Ԃ��擾[�ް��߯�ޑ���]
	// ���݉E���݂�����--------------------------------------
	if (Pad & PAD_INPUT_RIGHT)
	{
		// �����Ă���
		dir = DIR_RIGHT;
		InputNow[DIR_RIGHT] = PAD_INPUT_NOW;
	}
	else
	{
		// �����Ă��Ȃ�
		InputNow[DIR_RIGHT] = PAD_INPUT_OLD;
	}
	// �E���݂������Ă���u��
	if (InputNow[DIR_RIGHT] & ~InputOld[DIR_RIGHT])
	{
		pos.x += GRIDSIZE;
		// ���ق��߼޼�ݐ���
		if (tmp.x >= Scr.x - GRIDSIZE)
		{
			tmp.x = Scr.x - GRIDSIZE;
		}
	}
	// ---------------------------------------------------------

	// ���ݍ����݂�����-----------------------------------------
	if (Pad & PAD_INPUT_LEFT)
	{
		// �����Ă���
		dir = DIR_LEFT;
		InputNow[DIR_LEFT] = PAD_INPUT_NOW;
	}
	else
	{
		// �����Ă��Ȃ�
		InputNow[DIR_LEFT] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_LEFT] & ~InputOld[DIR_LEFT])
	{
		tmp.x -= GRIDSIZE;
		// ���ق��߼޼�ݐ���
		if (tmp.x <= 0)
		{
			tmp.x = 0;
		}
	}
	//--------------------------------------------------------

	// ���ݏ����݂�����---------------------------------------
	if (Pad & PAD_INPUT_UP)
	{
		// �����Ă���
		dir = DIR_UP;
		InputNow[dir] = PAD_INPUT_NOW;
	}
	else
	{
		// �����Ă��Ȃ�
		InputNow[DIR_UP] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_UP] & ~InputOld[DIR_UP])
	{
		tmp.y -= GRIDSIZE;
		// ���ق��߼޼�ݐ���
		if (tmp.y <= 0)
		{
			tmp.y = 0;
		}
	}
	//----------------------------------------------------

	// ���݉����݂�����-----------------------------------
	if (Pad & PAD_INPUT_DOWN)
	{
		// �����Ă���
		dir = DIR_DOWN;
		InputNow[dir] = PAD_INPUT_NOW;
	}
	else
	{
		// �����Ă��Ȃ� 
		InputNow[DIR_DOWN] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_DOWN] & ~InputOld[DIR_DOWN])
	{
		tmp.y += GRIDSIZE;
		// ���ق��߼޼�ݐ���
		if (tmp.y >= (Scr.y - GRIDSIZE) - 20)
		{
			tmp.y = (Scr.y - GRIDSIZE) - 20;
		}
	}
	//--------------------------------------------------------


	// id��i�߂鏈��---------------------------------------------
	if (Pad & PAD_INPUT_8)
	{
		ChangeInput = PAD_INPUT_NOW;
	}
	else
	{
		ChangeInput = PAD_INPUT_OLD;
	}

	if (ChangeInput & ~ChangeInputOld)
	{
		id = (objID)((id >= objID::NON) ? objID::PLAYER1 : id + 1);	//id+1 = Cursor�̱��݂̎�
	}
	//------------------------------------------------------------

	// id��߂�����-----------------------------------------------
	if (Pad & PAD_INPUT_7)
	{
		ChangeInputBack = PAD_INPUT_NOW;
	}
	else
	{
		ChangeInputBack = PAD_INPUT_OLD;
	}

	if (ChangeInputBack & ~ChangeInputBackOld)
	{
		id = (objID)((id <= objID::PLAYER1) ? objID::NON : id - 1);	//id+1 = Cursor�̱��݂̎�
	}
	//------------------------------------------------------------

	if (Pad & PAD_INPUT_6)
	{
		SetInput = PAD_INPUT_NOW;
	}
	else
	{
		SetInput = PAD_INPUT_OLD;
	}

	if (SetInput & ~SetInputOld)
	{
		setF = true;
		lpMap.setMapData(pos, id);

	}
	else
	{
		setF = false;
	}
	// �������u�Ԃ��擾[���ް�ޑ���]
	// ���݉E���݂�����--------------------------------------
	if (cnt_now[KEY_INPUT_RIGHT] & ~cnt_old[KEY_INPUT_RIGHT])
	{
		tmp.x += GRIDSIZE;
		individualsMapPos.x += GRIDSIZE;
		if (tmp.x >= lpMap.GetMapSize().x - (gridSize.x * 2))
		{
			tmp.x = (lpMap.GetMapSize().x - (gridSize.x * 2));
			individualsMapPos.x = lpMap.GetMapSize().x - GRIDSIZE * 5;
		}
		//mapPos.x = lpMap.MapCalcPos(tmp,cameraPos,mapPos).x;
		//tmpMappos.y = mapPos.y;
	}
	// ---------------------------------------------------------

	// ���ݍ����݂�����-----------------------------------------
	if (cnt_now[KEY_INPUT_LEFT] & ~cnt_old[KEY_INPUT_LEFT])
	{
		tmp.x -= GRIDSIZE;
		individualsMapPos.x -= GRIDSIZE;
		if (tmp.x <= 0)
		{
			tmp.x = 0;
			individualsMapPos.x = -GRIDSIZE * 4;
		}

		//mapPos.x = lpMap.MapCalcPos(tmp, cameraPos,mapPos).x;

		//tmpMappos.y = mapPos.y;
	}
	//--------------------------------------------------------

	// ���ݏ����݂�����---------------------------------------
	if (cnt_now[KEY_INPUT_UP] & ~cnt_old[KEY_INPUT_UP])
	{
		tmp.y -= GRIDSIZE;
		individualsMapPos.y -= GRIDSIZE;

		if (tmp.y <= 0)
		{
			tmp.y = 0;
			individualsMapPos.y = -GRIDSIZE * 4;
		}
		//tmpMappos.x = mapPos.x;
		//mapPos.y = lpMap.MapCalcPos(tmp, cameraPos,mapPos).y;
	}
	//----------------------------------------------------

	// ���݉����݂�����-----------------------------------
	if (cnt_now[KEY_INPUT_DOWN] & ~cnt_old[KEY_INPUT_DOWN])
	{
		tmp.y += GRIDSIZE;
		individualsMapPos.y += GRIDSIZE;

		if (tmp.y >= lpMap.GetMapSize().y - gridSize.y * 4)
		{
			tmp.y = lpMap.GetMapSize().y - gridSize.y * 4;
			individualsMapPos.y = lpMap.GetMapSize().y - GRIDSIZE * 5;

		}
		//tmpMappos.x = mapPos.x;
		//mapPos.y = lpMap.MapCalcPos(tmp, cameraPos,mapPos).y;
		/*if (tmpMappos.y <= -(lpMap.GetMapSize().y - 500))
		{
			mapPos.y = -(lpMap.MapCalcPos(tmp, cameraPos,mapPos).y - 500);
		}*/
	}

	//���ق̈ړ��i���X�ɑ����Ȃ��Ă��������j-----------------------------
	if (tmp != pos)								//���������Ă���Ԃ̏���
	{
		inputFrame++;								//���Z
		if (inputFrame >= keyDefRng)				//
		{
			pos = tmp;
			inputFrame = 0;							//���݂����𗣂����Ƃ�0�؂���
			keyDefRng /= 2;							//���݂����������Ă���Ƃ��񂾂����
			if (keyDefRng < EDITCURSOR_MIN_RNG)			//������5�ɂȂ����炻���ł�����5�ɂ���
			{
				keyDefRng = EDITCURSOR_MIN_RNG;
			}
		}
	}
	else
	{
		keyDefRng = EDITCURSOR_DEF_RNG;
		inputFrame = EDITCURSOR_DEF_RNG;
	}
	//-----------------------------------------------------------------------------


	//--------------------------------------------------------

	if (cnt_now[KEY_INPUT_RCONTROL] & ~cnt_old[KEY_INPUT_RCONTROL])
	{
		id = (objID)((id >= objID::NON) ? objID::PLAYER1 : id + 1);	//id+1 = Cursor�̱��݂̎�
	}
	//------------------------------------------------------------

	if (cnt_now[KEY_INPUT_LCONTROL] & ~cnt_old[KEY_INPUT_LCONTROL])
	{
		id = (objID)((id <= objID::PLAYER1) ? objID::NON : id - 1);	//id+1 = Cursor�̱��݂̎�
	}
	//-----------------------------------------------------------

	if (cnt_now[KEY_INPUT_SPACE] & ~cnt_old[KEY_INPUT_SPACE])
	{
		setF = true;
		lpMap.setMapData(tmp, id);
	}
	else
	{
		setF = false;
	}
	if (cnt_now[KEY_INPUT_P] && ~cnt_old[KEY_INPUT_P])
	{
		lpMap.setMapData(VECTOR2(GetRand(MAPSIZE_X - GRIDSIZE), GetRand(MAPSIZE_Y - GRIDSIZE)), (objID)(GetRand((int)objID::PLAYER3)));
	}
	_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", pos.x, pos.y, id);
}

void EditCursor::Draw(void)
{
	
	// ���ق����点�鏈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawBox(pos.x, pos.y, pos.x + 80, pos.y + 80, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flickCnt);
	
	switch (id)
	{
	case objID::PLAYER1:
	case objID::PLAYER2:
	case objID::PLAYER3:
		DrawGraph(cameraPos.x, cameraPos.y, lpImage.GetID("image/map1.png")[static_cast<int>(0)], true);
		break;
	case objID::WALL:
	case objID::CHAIR_1:
	case objID::CHAIR_2:
	case objID::CHAIR_3:
	case objID::CHAIR_4:
		DrawGraph(cameraPos.x, cameraPos.y, lpImage.GetID("image/map1.png")[static_cast<int>(id - 2)], true);
		break;
	case objID::BOOKSHELF:
	case objID::DRAWER:
	case objID::LOCKER:
	case objID::VASE_1:
	case objID::VASE_2:
		DrawGraph(cameraPos.x + GRIDSIZE, cameraPos.y - GRIDSIZE, lpImage.GetID("image/map2.png")[static_cast<int>(id - 8)], true);
		break;
	case objID::MIRRORTABLE:
	case objID::FACE:
	case objID::KITCHIN_1:
	case objID::KITCHIN_2:
	case objID::S_MONITOR:
		DrawGraph(cameraPos.x + GRIDSIZE, cameraPos.y - (GRIDSIZE * 2), lpImage.GetID("image/map3.png")[static_cast<int>(id - 13)], true);
		break;
	case objID::BED:
		DrawGraph(cameraPos.x + GRIDSIZE, cameraPos.y + GRIDSIZE, lpImage.GetID("image/map4.png")[0], true);
		break;
	case objID::DESK:
		DrawGraph(cameraPos.x, cameraPos.y, lpImage.GetID("image/map5.png")[0], true);
		break;
	case objID::MONITOR:
		DrawGraph(cameraPos.x + GRIDSIZE, cameraPos.y - (GRIDSIZE * 2), lpImage.GetID("image/map6.png")[0], true);
		break;
	case objID::S_TABLE:
		DrawGraph(cameraPos.x, cameraPos.y, lpImage.GetID("image/map7.png")[0], true);
		break;
	case objID::TABLE:
		DrawGraph(cameraPos.x, cameraPos.y, lpImage.GetID("image/map8.png")[0], true);
		break;
	default:
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	flickCnt += 5;
	if (flickCnt >= 300)
	{
		flickCnt = 0;
	}

	DrawFormatString(SCREENSIZE_X - 50, SCREENSIZE_Y - 50,0xff0000, "id:%d", id);

	if (setF)
	{
		DrawFormatString(SCREENSIZE_X - 100, SCREENSIZE_Y - 100, 0x00ff00, "id:%d", id);
	}
	DrawFormatString(50, 100, 0x00ff00, "pos.x:%d\npos.y:%d", pos.x, pos.y);
}

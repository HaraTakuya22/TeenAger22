#include <DxLib.h>
#include "Scene.h"
#include "Map.h"
#include "Image.h"
#include "EditCursor.h"


#define EDITCURSOR_DEF_RNG	(30)
#define EDITCURSOR_MIN_RNG	(5)

EditCursor::EditCursor(VECTOR2 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	cursorPos = { 0,0 };

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

	// �ް��߯�ނ̓���
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	auto cnt_now = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto cnt_old = controll.GetButtonInfo(KEY_TYPE_OLD);

	auto Scr = lpScene.GetScrSize();

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
		id = (objID)((id >= objID::NON) ? objID::FLOOR : id + 1);	//id+1 = Cursor�̱��݂̎�
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
		id = (objID)((id <= objID::FLOOR) ? objID::NON : id - 1);	//id+1 = Cursor�̱��݂̎�
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
	if (cnt_now[KEY_INPUT_RIGHT])
	{
		
		tmp.x += GRIDSIZE;

		//setId.set_pos.x -= GRIDSIZE;
		if (tmp.x > Scr.x - GRIDSIZE)
		{
			lpMap.GetMapPos().x -= GRIDSIZE;
			
		}

		// Map�̈ړ�����
		if (lpMap.GetMapPos().x <= -(Scr.x * 9))
		{
			// Map�̈ړ�����
			lpMap.GetMapPos().x = -(Scr.x * 9);
			// ���ق̈ړ�����
			if (tmp.x >= Scr.x - (GRIDSIZE * 2))
			{
				tmp.x = Scr.x - (GRIDSIZE * 2);
			}
		}
	}
	// ---------------------------------------------------------

	// ���ݍ����݂�����-----------------------------------------
	if (cnt_now[KEY_INPUT_LEFT])
	{
		tmp.x -= GRIDSIZE;
		
		if (tmp.x <= 0)
		{
			lpMap.GetMapPos().x += GRIDSIZE;
			tmp.x = 0;
		}
		// Map�̈ړ�����
		if (lpMap.GetMapPos().x + lpMap.GetMapSize().x >= lpMap.GetMapSize().x - Scr.x)
		{
			// Map�̈ړ�����
			lpMap.GetMapPos().x = 0;
			// ���ق��߼޼�ݐ���
			if (tmp.x <= GRIDSIZE)
			{
				tmp.x = GRIDSIZE;
			}
		}
	}
	//--------------------------------------------------------

	// ���ݏ����݂�����---------------------------------------
	if (cnt_now[KEY_INPUT_UP])
	{
		tmp.y -= GRIDSIZE;
		cursorPos.y -= GRIDSIZE;

		if (tmp.y <= 0)
		{
			lpMap.GetMapPos().y += GRIDSIZE;
			tmp.y = 0;
		}
		if (lpMap.GetMapPos().y + lpMap.GetMapSize().y >= lpMap.GetMapSize().y - Scr.y)
		{
			// Map�̈ړ�����
			lpMap.GetMapPos().y = 0;
			// ���ق��߼޼�ݐ���
			if (tmp.y <= GRIDSIZE)
			{
				tmp.y = GRIDSIZE;
			}
		}
	}
	//----------------------------------------------------

	// ���݉����݂�����-----------------------------------
	if (cnt_now[KEY_INPUT_DOWN])
	{
		tmp.y += GRIDSIZE;
		cursorPos.y += GRIDSIZE;
		if (tmp.y >= Scr.y - 20)
		{
			lpMap.GetMapPos().y -= GRIDSIZE;
			tmp.y = Scr.y - GRIDSIZE -20;
		}
		
		// Map�̈ړ�����
		if (lpMap.GetMapPos().y <= -((lpMap.GetMapSize().y - Scr.y) + 20))
		{
			// Map���߼޼�ݐ���
			lpMap.GetMapPos().y = -((lpMap.GetMapSize().y - Scr.y) + 20);
			if (tmp.y >= ((Scr.y - (GRIDSIZE * 2)) - 20))
			{
				tmp.y = ((Scr.y - (GRIDSIZE * 2)) - 20);
			}
		}
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
		id = (objID)((id >= objID::NON) ? objID::FLOOR : id + 1);	//id+1 = Cursor�̱��݂̎�
	}
	//------------------------------------------------------------

	if (cnt_now[KEY_INPUT_LCONTROL] & ~cnt_old[KEY_INPUT_LCONTROL])
	{
		id = (objID)((id <= objID::FLOOR) ? objID::NON : id - 1);	//id+1 = Cursor�̱��݂̎�
	}
	//-----------------------------------------------------------

	if (cnt_now[KEY_INPUT_SPACE] & ~cnt_old[KEY_INPUT_SPACE])
	{
		setF = true;
		lpMap.setMapData(VECTOR2(pos.x,pos.y), id);
	}
	else
	{
		setF = false;
	}
	_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", cursorPos.x,cursorPos.y, id);
	_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", tmp.x, tmp.y, id);

}

void EditCursor::Draw(void)
{
	// ���ق����点�鏈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawBox(pos.x, pos.y, pos.x + 80, pos.y + 80, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flickCnt);
	switch (id)
	{
	case objID::FLOOR:
	case objID::WALL:
	case objID::CHAIR_1:
	case objID::CHAIR_2:
	case objID::CHAIR_3:
	case objID::CHAIR_4:

		if (lpMap.GetMapPos().x >= 0)
		{
			DrawGraph(pos.x, pos.y, lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
		}
		/*else if (lpMap.GetMapPos().x <= 0)
		{
			DrawGraph(lpScene.GetScrSize().x - GRIDSIZE, pos.y, lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
		}*/
		break;
	case objID::BOOKSHELF:
	case objID::DRAWER:
	case objID::LOCKER:
	case objID::VASE_1:
	case objID::VASE_2:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map2.png")[static_cast<int>(id - 6)], true);
		break;
	case objID::MIRRORTABLE:
	case objID::FACE:
	case objID::KITCHIN_1:
	case objID::KITCHIN_2:
	case objID::S_MONITOR:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map3.png")[static_cast<int>(id - 11)], true);
		break;
	case objID::BED:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map4.png")[0], true);
		break;
	case objID::DESK:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map5.png")[0], true);
		break;
	case objID::MONITOR:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map6.png")[0], true);
		break;
	case objID::S_TABLE:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map7.png")[0], true);
		break;
	case objID::TABLE:
		DrawGraph(pos.x,pos.y, lpImage.GetID("image/map8.png")[0], true);
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
	DrawFormatString(50, 50, 0x00ff00, "cursorpos.x:%d\ncursorpos.y:%d", cursorPos.x, cursorPos.y);
	DrawFormatString(50, 100, 0x00ff00, "pos.x:%d\npos.y:%d", pos.x, pos.y);
	DrawFormatString(50, 150, 0x0000ff, "mapPos.x:%d\nmapPos.y:%d", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

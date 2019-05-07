#include <DxLib.h>
#include "Scene.h"
#include "Map.h"
#include "Image.h"
#include "EditCursor.h"



EditCursor::EditCursor(VECTOR2 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

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
	// πﬁ∞— ﬂØƒﬁÇÃì¸óÕ
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	auto Scr = lpScene.GetScrSize();

	// âüÇµÇΩèuä‘ÇéÊìæ
	// åªç›âEŒﬁ¿›Çâüâ∫--------------------------------------
	if (Pad & PAD_INPUT_RIGHT)
	{
		// âüÇµÇƒÇ¢ÇÈ
		dir = DIR_RIGHT;
		InputNow[DIR_RIGHT] = PAD_INPUT_NOW;
	}
	else
	{
		// âüÇµÇƒÇ¢Ç»Ç¢
		InputNow[DIR_RIGHT] = PAD_INPUT_OLD;
	}
	// âEŒﬁ¿›ÇâüÇµÇƒÇ¢ÇÈèuä‘
	if (InputNow[DIR_RIGHT] & ~InputOld[DIR_RIGHT])
	{
		pos.x += GRIDSIZE;
		// ∂∞øŸÇÃŒﬂºﬁºÆ›êßå‰
		if (pos.x >= Scr.x - GRIDSIZE)
		{
			pos.x = Scr.x - GRIDSIZE;
		}
	}
	// ---------------------------------------------------------

	// åªç›ç∂Œﬁ¿›Çâüâ∫-----------------------------------------
	if (Pad & PAD_INPUT_LEFT)
	{
		// âüÇµÇƒÇ¢ÇÈ
		dir = DIR_LEFT;
		InputNow[DIR_LEFT] = PAD_INPUT_NOW;
	}
	else
	{
		// âüÇµÇƒÇ¢Ç»Ç¢
		InputNow[DIR_LEFT] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_LEFT] & ~InputOld[DIR_LEFT])
	{
		pos.x -= GRIDSIZE;
		// ∂∞øŸÇÃŒﬂºﬁºÆ›êßå‰
		if (pos.x <= 0)
		{
			pos.x = 0;
		}
	}
	//--------------------------------------------------------

	// åªç›è„Œﬁ¿›Çâüâ∫---------------------------------------
	if (Pad & PAD_INPUT_UP)
	{
		// âüÇµÇƒÇ¢ÇÈ
		dir = DIR_UP;
		InputNow[dir] = PAD_INPUT_NOW;
	}
	else
	{
		// âüÇµÇƒÇ¢Ç»Ç¢
		InputNow[DIR_UP] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_UP] & ~InputOld[DIR_UP])
	{
		pos.y -= GRIDSIZE;
		// ∂∞øŸÇÃŒﬂºﬁºÆ›êßå‰
		if (pos.y <= 0)
		{
			pos.y = 0;
		}
	}
	//----------------------------------------------------

	// åªç›â∫Œﬁ¿›Çâüâ∫-----------------------------------
	if (Pad & PAD_INPUT_DOWN)
	{
		// âüÇµÇƒÇ¢ÇÈ
		dir = DIR_DOWN;
		InputNow[dir] = PAD_INPUT_NOW;
	}
	else
	{
		// âüÇµÇƒÇ¢Ç»Ç¢ 
		InputNow[DIR_DOWN] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_DOWN] & ~InputOld[DIR_DOWN])
	{
		pos.y += GRIDSIZE;
		// ∂∞øŸÇÃŒﬂºﬁºÆ›êßå‰
		if (pos.y >= (Scr.y - GRIDSIZE) - 20)
		{
			pos.y = (Scr.y - GRIDSIZE) - 20;
		}
	}
	//--------------------------------------------------------


	// idÇêiÇﬂÇÈèàóù---------------------------------------------
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
		id = (objID)((id >= objID::ID_NON) ? objID::ID_1 : id + 1);	//id+1 = CursorÇÃ±≤∫›ÇÃéü
	}
	//------------------------------------------------------------

	// idÇñﬂÇ∑èàóù-----------------------------------------------
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
		id = (objID)((id <= objID::ID_1) ? objID::ID_NON : id - 1);	//id+1 = CursorÇÃ±≤∫›ÇÃéü
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
}

void EditCursor::Draw(void)
{
	
	// ∂∞øŸÇåıÇÁÇπÇÈèàóù
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawBox(pos.x, pos.y, pos.x + 80, pos.y + 80, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flickCnt);
	DrawGraph(pos.x, pos.y, lpImage.GetID("image/chips.png")[static_cast<int>(id)], true);
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

}

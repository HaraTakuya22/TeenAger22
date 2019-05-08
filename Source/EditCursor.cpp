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

	// ｹﾞｰﾑﾊﾟｯﾄﾞの入力
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	auto cnt_now = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto cnt_old = controll.GetButtonInfo(KEY_TYPE_OLD);

	auto Scr = lpScene.GetScrSize();

	// 押した瞬間を取得[ｹﾞｰﾑﾊﾟｯﾄﾞ操作]
	// 現在右ﾎﾞﾀﾝを押下--------------------------------------
	if (Pad & PAD_INPUT_RIGHT)
	{
		// 押している
		dir = DIR_RIGHT;
		InputNow[DIR_RIGHT] = PAD_INPUT_NOW;
	}
	else
	{
		// 押していない
		InputNow[DIR_RIGHT] = PAD_INPUT_OLD;
	}
	// 右ﾎﾞﾀﾝを押している瞬間
	if (InputNow[DIR_RIGHT] & ~InputOld[DIR_RIGHT])
	{
		pos.x += GRIDSIZE;
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.x >= Scr.x - GRIDSIZE)
		{
			tmp.x = Scr.x - GRIDSIZE;
		}
	}
	// ---------------------------------------------------------

	// 現在左ﾎﾞﾀﾝを押下-----------------------------------------
	if (Pad & PAD_INPUT_LEFT)
	{
		// 押している
		dir = DIR_LEFT;
		InputNow[DIR_LEFT] = PAD_INPUT_NOW;
	}
	else
	{
		// 押していない
		InputNow[DIR_LEFT] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_LEFT] & ~InputOld[DIR_LEFT])
	{
		tmp.x -= GRIDSIZE;
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.x <= 0)
		{
			tmp.x = 0;
		}
	}
	//--------------------------------------------------------

	// 現在上ﾎﾞﾀﾝを押下---------------------------------------
	if (Pad & PAD_INPUT_UP)
	{
		// 押している
		dir = DIR_UP;
		InputNow[dir] = PAD_INPUT_NOW;
	}
	else
	{
		// 押していない
		InputNow[DIR_UP] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_UP] & ~InputOld[DIR_UP])
	{
		tmp.y -= GRIDSIZE;
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.y <= 0)
		{
			tmp.y = 0;
		}
	}
	//----------------------------------------------------

	// 現在下ﾎﾞﾀﾝを押下-----------------------------------
	if (Pad & PAD_INPUT_DOWN)
	{
		// 押している
		dir = DIR_DOWN;
		InputNow[dir] = PAD_INPUT_NOW;
	}
	else
	{
		// 押していない 
		InputNow[DIR_DOWN] = PAD_INPUT_OLD;
	}
	if (InputNow[DIR_DOWN] & ~InputOld[DIR_DOWN])
	{
		tmp.y += GRIDSIZE;
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.y >= (Scr.y - GRIDSIZE) - 20)
		{
			tmp.y = (Scr.y - GRIDSIZE) - 20;
		}
	}
	//--------------------------------------------------------


	// idを進める処理---------------------------------------------
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
		id = (objID)((id >= objID::NON) ? objID::FLOOR : id + 1);	//id+1 = Cursorのｱｲｺﾝの次
	}
	//------------------------------------------------------------

	// idを戻す処理-----------------------------------------------
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
		id = (objID)((id <= objID::FLOOR) ? objID::NON : id - 1);	//id+1 = Cursorのｱｲｺﾝの次
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
	// 押した瞬間を取得[ｷｰﾎﾞｰﾄﾞ操作]
	// 現在右ﾎﾞﾀﾝを押下--------------------------------------
	if (cnt_now[KEY_INPUT_RIGHT])
	{
		tmp.x += GRIDSIZE;
		lpMap.GetMapPos().x -= GRIDSIZE;
		// Mapの移動制御
		if (lpMap.GetMapPos().x <= -(Scr.x * 3))
		{
			lpMap.GetMapPos().x = -(Scr.x * 3);
		}
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.x >= Scr.x - GRIDSIZE)
		{
			//lpMap.GetMapPos().x += Scr.x;
			tmp.x = Scr.x - GRIDSIZE;
		}
	}
	
	// ---------------------------------------------------------

	// 現在左ﾎﾞﾀﾝを押下-----------------------------------------
	if (cnt_now[KEY_INPUT_LEFT])
	{
		tmp.x -= GRIDSIZE;
		lpMap.GetMapPos().x += GRIDSIZE;
		// Mapの移動制御
		if (lpMap.GetMapPos().x + lpMap.GetMapSize().x >= lpMap.GetMapSize().x - Scr.x)
		{
			lpMap.GetMapPos().x = 0;
		}

		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.x <= 0)
		{
			tmp.x = 0;
		}
	}
	
	//--------------------------------------------------------

	// 現在上ﾎﾞﾀﾝを押下---------------------------------------
	if (cnt_now[KEY_INPUT_UP])
	{
		tmp.y -= GRIDSIZE;
		lpMap.GetMapPos().y += GRIDSIZE;
		if (lpMap.GetMapPos().y + lpMap.GetMapSize().y >= lpMap.GetMapSize().y - Scr.y)
		{
			lpMap.GetMapPos().y = 0;
		}
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.y <= 0)
		{
			tmp.y = 0;
		}
	}
	//----------------------------------------------------

	// 現在下ﾎﾞﾀﾝを押下-----------------------------------
	if (cnt_now[KEY_INPUT_DOWN])
	{
		tmp.y += GRIDSIZE;
		lpMap.GetMapPos().y -= GRIDSIZE;
		// Mapの移動制御
		if (lpMap.GetMapPos().y <= -((Scr.y * 4) - (GRIDSIZE * 6)))
		{
			lpMap.GetMapPos().y = -((Scr.y * 4) - (GRIDSIZE * 6));
		}
		// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ制御
		if (tmp.y >= (Scr.y - GRIDSIZE) - 20)
		{
			tmp.y = (Scr.y - GRIDSIZE) - 20;
		}
	}

	//ｶｰｿﾙの移動（徐々に速くなっていく処理）-----------------------------
	if (tmp != pos)								//ｷｰを押している間の処理
	{
		inputFrame++;								//加算
		if (inputFrame >= keyDefRng)				//
		{
			pos = tmp;
			inputFrame = 0;							//ﾎﾞﾀﾝから手を離したとき0ｸﾘする
			keyDefRng /= 2;							//ﾎﾞﾀﾝを押し続けているとだんだん加速
			if (keyDefRng < EDITCURSOR_MIN_RNG)			//加速が5になったらそこでずっと5にする
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
		id = (objID)((id >= objID::NON) ? objID::FLOOR : id + 1);	//id+1 = Cursorのｱｲｺﾝの次
	}
	//------------------------------------------------------------

	if (cnt_now[KEY_INPUT_LCONTROL] & ~cnt_old[KEY_INPUT_LCONTROL])
	{
		id = (objID)((id <= objID::FLOOR) ? objID::NON : id - 1);	//id+1 = Cursorのｱｲｺﾝの次
	}
	//-----------------------------------------------------------

	if (cnt_now[KEY_INPUT_SPACE] & ~cnt_old[KEY_INPUT_SPACE])
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
	
	// ｶｰｿﾙを光らせる処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawBox(pos.x, pos.y, pos.x + 80, pos.y + 80, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flickCnt);
	DrawGraph(pos.x, pos.y, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true);
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

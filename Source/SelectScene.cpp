#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EditScene.h"
#include "GameScene.h"
#include "Controller.h"

#define ONE_PLAY_POS 20+(360/2)-100
#define TWO_PLAY_POS 20+400+(360/2)-100
#define THREE_PLAY_POS 20+800+(360/2)-100

#define CURSOR_POS_SPEED 400

SelectScene::SelectScene()
{
	Init();
	SetCreateSoundTimeStretchRate(2.0f);
	PlaySoundFile("音源/sample6.mp3", DX_PLAYTYPE_LOOP);
}

SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Update(unique_Base own, const Controller & controll)
{
	// ｹﾞｰﾑﾊﾟｯﾄﾞの入力
	inputRightOld = inputRightNow;
	inputLeftOld = inputLeftNow;
	inputStartOld = inputStartNow;

	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	auto cnt_now = controll.GetKeyButtonInfo(KEY_TYPE_NOW);
	auto cnt_old = controll.GetKeyButtonInfo(KEY_TYPE_OLD);

	if (cursorPos.x < ONE_PLAY_POS)
	{
		cursorPos.x = THREE_PLAY_POS;
	}
	if (cursorPos.x > THREE_PLAY_POS)
	{
		cursorPos.x = ONE_PLAY_POS;
	}

	if (cursorPos.x == ONE_PLAY_POS)
	{
		button1_flag = BUTTON_ON;
		if (cnt_now[KEY_INPUT_SPACE])
		{
			lpMap.playerCnt = 1;
			//return std::make_unique<GameScene>();
		}
	}
	else
	{
		button1_flag = BUTTON_OFF;
	}

	if (cursorPos.x == TWO_PLAY_POS)
	{
		button2_flag = BUTTON_ON;
		if (cnt_now[KEY_INPUT_SPACE])
		{
			lpMap.playerCnt = 2;
			//return std::make_unique<GameScene>();
		}
	}
	else
	{
		button2_flag = BUTTON_OFF;
	}
	if (cursorPos.x == THREE_PLAY_POS)
	{
		button3_flag = BUTTON_ON;
		if (cnt_now[KEY_INPUT_SPACE])
		{
			lpMap.playerCnt = 3;
			//return std::make_unique<GameScene>();
		}
	}
	else
	{
		button3_flag = BUTTON_OFF;
	}
	if (cnt_now[KEY_INPUT_I])
	{
		lpMap.playerCnt = 4;
		return std::make_unique<GameScene>();
	}
	// 操作関係------------------------------------------
	// 1Pの選択操作
	switch (lpMap.playerCnt)
	{
	case 1:
		if (typeNum2 != PREY_1 && typeNum3 != PREY_1)
		{
			if (cnt_now[KEY_INPUT_1])
			{
				typeNum1 = PREY_1;
			}
		}
		if (typeNum2 != PREY_2 && typeNum3 != PREY_2)
		{
			if (cnt_now[KEY_INPUT_2])
			{
				typeNum1 = PREY_2;
			}
		}
		if (typeNum2 != PREY_3 && typeNum3 != PREY_3)
		{
			if (cnt_now[KEY_INPUT_3])
			{
				typeNum1 = PREY_3;
			}
		}
		break;

	case 2:
		if (typeNum2 != PREY_1 && typeNum3 != PREY_1)
		{
			if (cnt_now[KEY_INPUT_1])
			{
				typeNum1 = PREY_1;
			}
		}
		if (typeNum2 != PREY_2 && typeNum3 != PREY_2)
		{
			if (cnt_now[KEY_INPUT_2])
			{
				typeNum1 = PREY_2;
			}
		}
		if (typeNum2 != PREY_3 && typeNum3 != PREY_3)
		{
			if (cnt_now[KEY_INPUT_3])
			{
				typeNum1 = PREY_3;
			}
		}
		// 2Pの選択操作
		if (typeNum1 != PREY_1 && typeNum3 != PREY_1)
		{
			if (cnt_now[KEY_INPUT_NUMPAD1])
			{
				typeNum2 = PREY_1;
			}
		}
		if (typeNum1 != PREY_2 && typeNum3 != PREY_2)
		{
			if (cnt_now[KEY_INPUT_NUMPAD2])
			{
				typeNum2 = PREY_2;
			}
		}
		if (typeNum1 != PREY_3 && typeNum3 != PREY_3)
		{
			if (cnt_now[KEY_INPUT_NUMPAD3])
			{
				typeNum2 = PREY_3;
			}
		}
		break;

	case 3:
		if (typeNum2 != PREY_1 && typeNum3 != PREY_1)
		{
			if (cnt_now[KEY_INPUT_1])
			{
				typeNum1 = PREY_1;
			}
		}
		if (typeNum2 != PREY_2 && typeNum3 != PREY_2)
		{
			if (cnt_now[KEY_INPUT_2])
			{
				typeNum1 = PREY_2;
			}
		}
		if (typeNum2 != PREY_3 && typeNum3 != PREY_3)
		{
			if (cnt_now[KEY_INPUT_3])
			{
				typeNum1 = PREY_3;
			}
		}

		// 2Pの選択操作
		if (typeNum1 != PREY_1 && typeNum3 != PREY_1)
		{
			if (cnt_now[KEY_INPUT_NUMPAD1])
			{
				typeNum2 = PREY_1;
			}
		}
		if (typeNum1 != PREY_2 && typeNum3 != PREY_2)
		{
			if (cnt_now[KEY_INPUT_NUMPAD2])
			{
				typeNum2 = PREY_2;
			}
		}
		if (typeNum1 != PREY_3 && typeNum3 != PREY_3)
		{
			if (cnt_now[KEY_INPUT_NUMPAD3])
			{
				typeNum2 = PREY_3;
			}
		}

		// 3Pの選択操作
		if (typeNum1 != PREY_1 && typeNum2 != PREY_1)
		{
			if (cnt_now[KEY_INPUT_7])
			{
				typeNum3 = PREY_1;
			}
		}
		if (typeNum1 != PREY_2 && typeNum2 != PREY_2)
		{
			if (cnt_now[KEY_INPUT_8])
			{
				typeNum3 = PREY_2;
			}
		}
		if (typeNum1 != PREY_3 && typeNum2 != PREY_3)
		{
			if (cnt_now[KEY_INPUT_9])
			{
				typeNum3 = PREY_3;
			}
		}
		
		break;

	default:
		break;
	}
	
	// ---------------------------------------------------

	if ((lpMap.playerCnt == 1) && (typeNum1 >= PREY_1 && typeNum1 <= PREY_3))
	{
		if (CheckHitKey(KEY_INPUT_V))
		{
			SetCreateSoundTimeStretchRate(0.5f);
			PlaySoundFile("音源/効果音5.mp3", DX_PLAYTYPE_NORMAL);
			return std::make_unique<GameScene>();
		}
	}
	if ((lpMap.playerCnt == 2) && ((typeNum1 >= PREY_1 && typeNum1 <= PREY_3) && (typeNum2 >= PREY_1 && typeNum2 <= PREY_3)))
	{
		if (CheckHitKey(KEY_INPUT_V))
		{
			SetCreateSoundTimeStretchRate(0.5f);
			PlaySoundFile("音源/効果音5.mp3", DX_PLAYTYPE_NORMAL);
			return std::make_unique<GameScene>();
		}
	}
	if ((lpMap.playerCnt == 3) && ((typeNum1 >= PREY_1 && typeNum1 <= PREY_3) && (typeNum2 >= PREY_1 && typeNum2 <= PREY_3) && (typeNum3 >= PREY_1 && typeNum3 <= PREY_3)))
	{
		if (CheckHitKey(KEY_INPUT_V))
		{
			SetCreateSoundTimeStretchRate(0.5f);
			PlaySoundFile("音源/効果音5.mp3", DX_PLAYTYPE_NORMAL);
			return std::make_unique<GameScene>();
		}
	}
	// 現在右ﾎﾞﾀﾝを押下--------------------------------------
	if ((Pad & PAD_INPUT_RIGHT) || (cnt_now[KEY_INPUT_RIGHT]) && (!cnt_old[KEY_INPUT_RIGHT]))
	{
		// 押している
		inputRightNow = PAD_INPUT_NOW;
	}
	else
	{
		// 押していない
		inputRightNow = PAD_INPUT_OLD;
	}
	// 右ﾎﾞﾀﾝを押している瞬間
	if (inputRightNow & ~inputRightOld)
	{
		cursorPos.x += CURSOR_POS_SPEED;
	}

	// 現在左ﾎﾞﾀﾝを押下-----------------------------------------
	if ((Pad & PAD_INPUT_LEFT) || (cnt_now[KEY_INPUT_LEFT]) && (!cnt_old[KEY_INPUT_LEFT]))
	{
		// 押している
		inputLeftNow = PAD_INPUT_NOW;
	}
	else
	{
		// 押していない
		inputLeftNow = PAD_INPUT_OLD;
	}
	// 左ﾎﾞﾀﾝを押している瞬間
	if (inputLeftNow & ~inputLeftOld)
	{
		cursorPos.x -= CURSOR_POS_SPEED;
	}

	ClsDrawScreen();

	Draw();

	ScreenFlip();
	return move(own);
}

int SelectScene::Init(void)
{
	LoadDivGraph("image/button_red_hakkou_one.png", 2, 1, 2, 360, 240, button1);
	LoadDivGraph("image/button_red_hakkou_two.png", 2, 1, 2, 360, 240, button2);
	LoadDivGraph("image/button_red_hakkou_three.png", 2, 1, 2, 360, 240, button3);
	cursorImage = LoadGraph("image/select_cursor.png");

	button1_flag = BUTTON_OFF;
	button2_flag = BUTTON_OFF;
	button3_flag = BUTTON_OFF;
	one_pos = { 0,0 };
	two_pos = { 0,0 };
	three_pos = { 0,0 };

	cursorPos = { ONE_PLAY_POS,150 };

	titleMapImage = LoadGraph("MAP/map(old).png");

	lpMap.playerCnt = 0;

	return 0;
}

void SelectScene::Draw(void)
{
	DrawExtendGraph(0, 0,
		1200 + 1, 660 + 1,
		titleMapImage,
		false);

	DrawGraph(20, 220, button1[button1_flag], true);
	DrawGraph(20 + 400, 220, button2[button2_flag], true);
	DrawGraph(20 + 800, 220, button3[button3_flag], true);
	DrawGraph(cursorPos.x, cursorPos.y, cursorImage, true);



	DrawFormatString(100, 50,0xffffff,"selectMode:%d\nselect1Num:%d\nselect2Num:%d\nselect3Num:%d", lpMap.playerCnt, typeNum1, typeNum2, typeNum3);
}

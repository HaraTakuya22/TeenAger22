#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EditScene.h"
#include "GameScene.h"
#include "Controller.h"

#define ONE_PLAY_POS 20+(360/2)-100
#define TWO_PLAY_POS (20+400)+(360/2)-100
#define THREE_PLAY_POS (20+800)+(360/2)-100

#define CURSOR_POS_SPEED 400

SelectScene::SelectScene()
{
	Init();
}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Update(unique_Base own, const Controller & controll)
{
	// �ް��߯�ނ̓���
	inputRightOld = inputRightNow;
	inputLeftOld = inputLeftNow;
	inputStartOld = inputStartNow;

	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	auto cnt_now = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto cnt_old = controll.GetButtonInfo(KEY_TYPE_OLD);

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
			lpMap.player = PLAYER_1;
			return std::make_unique<GameScene>();

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
			lpMap.player = PLAYER_2;
			return std::make_unique<GameScene>();

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
			lpMap.player = PLAYER_3;
			return std::make_unique<GameScene>();

		}
	}
	else
	{
		button3_flag = BUTTON_OFF;
	}

	if (cnt_now[KEY_INPUT_I])
	{
		lpMap.player = PLAYER_IT;
		return std::make_unique<GameScene>();
	}

	// ���݉E���݂�����--------------------------------------
	if ((Pad & PAD_INPUT_RIGHT) || (cnt_now[KEY_INPUT_RIGHT]) && (!cnt_old[KEY_INPUT_RIGHT]))
	{
		// �����Ă���
		inputRightNow = PAD_INPUT_NOW;
	}
	else
	{
		// �����Ă��Ȃ�
		inputRightNow = PAD_INPUT_OLD;
	}
	// �E���݂������Ă���u��
	if (inputRightNow & ~inputRightOld)
	{
		cursorPos.x += CURSOR_POS_SPEED;
	}

	// ���ݍ����݂�����-----------------------------------------
	if ((Pad & PAD_INPUT_LEFT) || (cnt_now[KEY_INPUT_LEFT]) && (!cnt_old[KEY_INPUT_LEFT]))
	{
		// �����Ă���
		inputLeftNow = PAD_INPUT_NOW;
	}
	else
	{
		// �����Ă��Ȃ�
		inputLeftNow = PAD_INPUT_OLD;
	}
	// �����݂������Ă���u��
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

	cursorPos = { ONE_PLAY_POS,150 };

	titleMapImage = LoadGraph("MAP/map(old).png");

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
}

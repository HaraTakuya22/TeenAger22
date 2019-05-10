#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EditScene.h"
#include "GameScene.h"
#include "Controller.h"

#define ONE_PLAY_POS 20
#define TWO_PLAY_POS 20+400
#define THREE_PLAY_POS 20+800

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
	if (CheckHitKey(KEY_INPUT_1))
	{
		lpMap.player = PLAYER_1;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		lpMap.player = PLAYER_2;
	}
	if (CheckHitKey(KEY_INPUT_3))
	{
		lpMap.player = PLAYER_3;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) &&
		(lpMap.player == PLAYER_1
			|| lpMap.player == PLAYER_2
			|| lpMap.player == PLAYER_3))
	{
		return std::make_unique<EditScene>();
	}
	
	if (cursorPos.x == ONE_PLAY_POS)
	{
		button1[BUTTON_OFF] = button1[BUTTON_ON];
	}
	
	if (cursorPos.x == TWO_PLAY_POS)
	{
		button2[BUTTON_OFF] = button2[BUTTON_ON];
	}
	
	if (cursorPos.x == THREE_PLAY_POS)
	{
		button3[BUTTON_OFF] = button3[BUTTON_ON];
	}
	

	auto cnt_now = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto cnt_old = controll.GetButtonInfo(KEY_TYPE_OLD);

	// åªç›âEŒﬁ¿›Çâüâ∫--------------------------------------
	if ((cnt_now[KEY_INPUT_RIGHT]) && (!cnt_old[KEY_INPUT_RIGHT]))
	{
		cursorPos.x += CURSOR_POS_SPEED;
	}

	// åªç›ç∂Œﬁ¿›Çâüâ∫-----------------------------------------
	if (cnt_now[KEY_INPUT_LEFT])
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
	LoadDivGraph("image/button_hakkou_one.png", 2, 1, 2, 360, 240, button1);
	LoadDivGraph("image/button_hakkou_two.png", 2, 1, 2, 360, 240, button2);
	LoadDivGraph("image/button_hakkou_three.png", 2, 1, 2, 360, 240, button3);
	one_pos = { 0,0 };
	two_pos = { 0,0 };
	three_pos = { 0,0 };

	cursorPos = { ONE_PLAY_POS,220 };

	titleMapImage = LoadGraph("MAP/map(old).png");

	return 0;
}

void SelectScene::Draw(void)
{
	DrawExtendGraph(0, 0,
		1200 + 1, 660 + 1,
		titleMapImage,
		false);

	DrawGraph(20, 220, button1[BUTTON_OFF], true);
	DrawGraph(20 + 400, 220, button2[BUTTON_OFF], true);
	DrawGraph(20 + 800, 220, button3[BUTTON_OFF], true);
}

#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EditScene.h"
#include "GameScene.h"

// startButtonの拡大数値
#define START_BUTTON_DON 2

TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own, const Controller & controll)
{
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	// スタートボタンで進む
	if(Pad & PAD_INPUT_12)
	{
		return std::make_unique<SelectScene>();
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		return std::make_unique<SelectScene>();
	}

	// マップの移動
	if ((titleRightPos.x >= 1200) && (titleRightPos.y >= 1440))
	{
		titleLeftPos.x = titleLeftPos.x - moveSpeed;
		titleRightPos.x = titleRightPos.x - moveSpeed;
	}
	if ((titleRightPos.x <= 1200) && (titleRightPos.y >= 660))
	{
		titleLeftPos.y = titleLeftPos.y - moveSpeed;
		titleRightPos.y = titleRightPos.y - moveSpeed;
	}
	if ((titleLeftPos.x <= 0) && (titleRightPos.y <= 660))
	{
		titleLeftPos.x = titleLeftPos.x + moveSpeed;
		titleRightPos.x = titleRightPos.x + moveSpeed;
	}
	if ((titleLeftPos.x >= 0) && (titleLeftPos.y <= 0))
	{
		titleLeftPos.y = titleLeftPos.y + moveSpeed;
		titleRightPos.y = titleRightPos.y + moveSpeed;
	}
	startButtonCnt++;
	// startButtonの表示の拡大縮小
	if ((startButtonCnt/5)%20 == 2)
	{
		startPos1 = { buttonLeftX -= START_BUTTON_DON,buttonLeftY -= START_BUTTON_DON };
		startPos2 = { buttonRightX += START_BUTTON_DON,buttonLeftY -= START_BUTTON_DON };
		startPos3 = { buttonRightX += START_BUTTON_DON,buttonRightY += START_BUTTON_DON };
		startPos4 = { buttonLeftX -= START_BUTTON_DON ,buttonRightY += START_BUTTON_DON };
	}
	else if ((startButtonCnt / 5) % 20 == 1)
	{
		startPos1 = { buttonLeftX += START_BUTTON_DON,buttonLeftY += START_BUTTON_DON };
		startPos2 = { buttonRightX -= START_BUTTON_DON,buttonLeftY += START_BUTTON_DON };
		startPos3 = { buttonRightX -= START_BUTTON_DON,buttonRightY -= START_BUTTON_DON };
		startPos4 = { buttonLeftX += START_BUTTON_DON,buttonRightY -= START_BUTTON_DON };

	}
	ClsDrawScreen();

	Draw();

	ScreenFlip();


	return move(own);
}

int TitleScene::Init(void)
{
	titleImage = LoadGraph("image/Title.png");

	titleMapImage = LoadGraph("MAP/map(old).png");
	startButtonImage = LoadGraph("image/TitleStart.png");
	titleLeftPos = { 0 , 0 };
	titleRightPos.x = 2400;
	titleRightPos.y = 1440;
	moveSpeed = 2;
	buttonLeftX = 250;
	buttonLeftY = 500;
	buttonRightX = 950;
	buttonRightY = 560;
	startPos1 = { buttonLeftX,buttonLeftY };
	startPos2 = { buttonRightX,buttonLeftY };
	startPos3 = { buttonRightX,buttonRightY };
	startPos4 = { buttonLeftX,buttonRightY };
	startButtonCnt = 0;
	return 0;
}

void TitleScene::Draw(void)
{
	DrawExtendGraph(titleLeftPos.x, titleLeftPos.y,
		titleRightPos.x + 1, titleRightPos.y + 1,
		titleMapImage,
		false);

	auto scr = lpScene.GetScrSize();
	//DrawFormatString(600, 0, 0xffff00, "title");

	// Titleﾛｺﾞの配置位置(仮)
	DrawGraph(0, 0, titleImage, true);

	// ｹﾞｰﾑ選択文字の配置位置(仮)
	//for (int i = 20; i <= 80; i *= 4)
	//{
	//	DrawBox((scr.x / 2) - 80, ((scr.y / 2) - 40) + i, (scr.x / 2) + 80, (scr.y / 2) + i, 0x00ff00, false);
	//}

	// StartButtonの表示
	DrawModiGraph(startPos1.x, startPos1.y,
		startPos2.x, startPos2.y,
		startPos3.x, startPos3.y,
		startPos4.x, startPos4.y,
				startButtonImage, true);
}

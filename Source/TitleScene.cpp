#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EditScene.h"
#include "GameScene.h"


TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own, const Controller & Controller)
{
	
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
	
	ClsDrawScreen();

	Draw();

	ScreenFlip();


	return move(own);
}

int TitleScene::Init(void)
{
	titleMapImage = LoadGraph("MAP/map(old).png");
	titleLeftPos = { 0 , 0 };
	titleRightPos.x = 2400;
	titleRightPos.y = 1440;
	moveSpeed = 2;
	return 0;
}

void TitleScene::Draw(void)
{
	DrawExtendGraph(titleLeftPos.x, titleLeftPos.y,
		titleRightPos.x + 1, titleRightPos.y + 1,
		titleMapImage,
		false);

	auto scr = lpScene.GetScrSize();
	DrawFormatString(600, 0, 0xffff00, "title");

	// Titleﾛｺﾞの配置位置(仮)
	DrawBox((scr.x / 2) - 150, (scr.y / 2) - 200, (scr.x / 2) + 150, (scr.y / 2) - 150,  0x0000ff, false);

	// ｹﾞｰﾑ選択文字の配置位置(仮)
	for (int i = 20; i <= 80; i *= 4)
	{
		DrawBox((scr.x / 2) - 80, ((scr.y / 2) - 40) + i, (scr.x / 2) + 80, (scr.y / 2) + i, 0x00ff00, false);
	}

}

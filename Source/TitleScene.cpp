#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
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
	//// ﾃﾞﾊﾞｯｸﾞ用-----------------------------------
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
	// --------------------------------------
	if (CheckHitKey(KEY_INPUT_RETURN) &&
		(lpMap.player == PLAYER_1
			|| lpMap.player == PLAYER_2
			|| lpMap.player == PLAYER_3))
	{
		return std::make_unique<EditScene>();
	}
	// マップの移動
	if ((titleRightPos.x >= 1200) && (titleRightPos.y >= 1440))
	{
		titleLeftPos.x = titleLeftPos.x - 3;
		titleRightPos.x = titleRightPos.x - 3;
	}
	if ((titleRightPos.x <= 1200) && (titleRightPos.y >= 660))
	{
		titleLeftPos.y = titleLeftPos.y - 3;
		titleRightPos.y = titleRightPos.y - 3;
	}
	if ((titleLeftPos.x <= 0) && (titleRightPos.y <= 660))
	{
		titleLeftPos.x = titleLeftPos.x + 3;
		titleRightPos.x = titleRightPos.x + 3;
	}
	if ((titleLeftPos.x >= 0) && (titleLeftPos.y <= 0))
	{
		titleLeftPos.y = titleLeftPos.y + 3;
		titleRightPos.y = titleRightPos.y + 3;
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

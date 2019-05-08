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
	//// ���ޯ�ޗp-----------------------------------
	//if (CheckHitKey(KEY_INPUT_1))
	//{
	//	lpMap.player = PLAYER_1;
	//}
	//if (CheckHitKey(KEY_INPUT_2))
	//{
	//	lpMap.player = PLAYER_2;
	//}
	//if (CheckHitKey(KEY_INPUT_3))
	//{
	//	lpMap.player = PLAYER_3;
	//}
	//// --------------------------------------
	//if (CheckHitKey(KEY_INPUT_RETURN) &&
	//	(lpMap.player == PLAYER_1
	//		|| lpMap.player == PLAYER_2
	//		|| lpMap.player == PLAYER_3))
	//{
	//	return std::make_unique<EditScene>();
	//}
	//ClsDrawScreen();
	//Draw();

	//ScreenFlip();


	return move(own);
}

int TitleScene::Init(void)
{

	return 0;
}

void TitleScene::Draw(void)
{
	auto scr = lpScene.GetScrSize();
	DrawFormatString(600, 0, 0xffff00, "title");

	// Titleۺނ̔z�u�ʒu(��)
	DrawBox((scr.x / 2) - 150, (scr.y / 2) - 200, (scr.x / 2) + 150, (scr.y / 2) - 150,  0x0000ff, false);

	// �ްёI�𕶎��̔z�u�ʒu(��)
	for (int i = 20; i <= 80; i *= 4)
	{
		DrawBox((scr.x / 2) - 80, ((scr.y / 2) - 40) + i, (scr.x / 2) + 80, (scr.y / 2) + i, 0x00ff00, false);
	}
}

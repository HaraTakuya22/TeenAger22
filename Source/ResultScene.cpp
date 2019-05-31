#include <DxLib.h>
#include "Prey.h"
#include "It.h"
#include "Obj.h"
#include "Map.h"
#include "Scene.h"
#include "EditScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"



ResultScene::ResultScene()
{
	Init();

}


ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Update(unique_Base own, const Controller & controll)
{
	auto cnt_now = controll.GetButtonInfo()[KEY_TYPE_NOW];
	auto cnt_old = controll.GetButtonInfo()[KEY_TYPE_OLD];

	auto key_now = controll.GetKeyButtonInfo(KEY_TYPE_NOW);
	auto key_old = controll.GetKeyButtonInfo(KEY_TYPE_OLD);
	if (key_now[KEY_INPUT_RETURN] && !lpMap.Get_isScale())
	{
		return std::make_unique<SelectScene>();
	}

	ClsDrawScreen();
	Draw();
	ScreenFlip();


	return move(own);
}

int ResultScene::Init(void)
{
	timeUpImage = LoadGraph("image/TimeUp.png");
	return 0;
}

void ResultScene::Draw(void)
{
	DrawGraph(300, 100, timeUpImage, true);
}

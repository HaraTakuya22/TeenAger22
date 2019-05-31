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

unique_Base ResultScene::Update(unique_Base own, const Controller & Controller)
{
	auto input = Controller.GetButtonInfo(KEY_TYPE_NOW);
	auto inputOld = Controller.GetButtonInfo(KEY_TYPE_OLD);
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);

	if (input[KEY_INPUT_RETURN] && !lpMap.Get_isScale())
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

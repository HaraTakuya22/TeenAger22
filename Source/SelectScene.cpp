#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EditScene.h"
#include "GameScene.h"



SelectScene::SelectScene()
{
}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Update(unique_Base own, const Controller & Controller)
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
	ClsDrawScreen();

	Draw();

	ScreenFlip();
	return move(own);
}

int SelectScene::Init(void)
{
	return 0;
}

void SelectScene::Draw(void)
{
}

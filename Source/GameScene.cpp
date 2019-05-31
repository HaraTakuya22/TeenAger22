#include <DxLib.h>
#include "PLAYER.h"
#include "Prey.h"
#include "Obj.h"
#include "Scene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "ResultScene.h"
#include "Camera.h"

#include "Map.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own, const Controller & Controller)
{
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);
	auto Scr = lpScene.GetScrSize();

	
	// objListÇÃ±ØÃﬂ√ﬁ∞ƒ
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}



	switch (lpMap.playerCnt)
	{
	case 1:
		lpMap.camera[static_cast<int>(PLAYER::PLAYER_1)].Update(Controller);

		break;

	case 2:
		lpMap.camera[static_cast<int>(PLAYER::PLAYER_1)].Update(Controller);
		lpMap.camera[static_cast<int>(PLAYER::PLAYER_2)].Update(Controller);
		break;

	case 3:
		for (int player = 1; player <= 3; player++)
		{
			lpMap.camera[static_cast<int>(player)].Update(Controller);
		}
		break;
	default:
		break;
	}
	


	

	// πﬁ∞— ﬂØƒﬁÇÃBack∑∞Çâüâ∫ Å® EditSceneÇ…à⁄çs
	if (Pad & PAD_INPUT_11)
	{
		return std::make_unique<EditScene>();
	}

	// πﬁ∞— ﬂØƒﬁÇÃBack∑∞Çâüâ∫ Å® EditSceneÇ…à⁄çs
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		return std::make_unique<EditScene>();
	}
	
	if (500 < (GetNowCount() - startTime) && (GetNowCount() - startTime) <= 1500)
	{
		countDownFlag = true;
		countDown = 0;
	}
	if (1500 < (GetNowCount() - startTime) && (GetNowCount() - startTime) <= 2500)
	{
		countDown = 1;
	}
	if (2500 < (GetNowCount() - startTime) && (GetNowCount() - startTime) <= 3500)
	{
		countDown = 2;
	}
	if (3500 < (GetNowCount() - startTime) && (GetNowCount() - startTime) <= 4500)
	{
		countDown = 3;
	}
	if (4500 < (GetNowCount() - startTime) && (GetNowCount() - startTime) <= 5000)
	{
		countDownFlag = false;
	}

	if (GetNowCount() - startTime > 3000 + 5000)
	{
		timeUpFlag = true;
	}
	if (GetNowCount() - startTime > 10000)
	{
	return std::make_unique<ResultScene>();
	}

	ClsDrawScreen();
	Draw();
	ScreenFlip();


	return move(own);
}

int GameScene::Init(void)
{
	itTimeUpImage = LoadGraph("image/TimeUp.png");
	LoadDivGraph("image/CountDown.png", 4, 4, 1, 600, 600, countDownImage);

	if (!objlist)
	{
		objlist = std::make_shared<Shared_ObjList>();
	}

	VECTOR2 gridSize = lpMap.GetGridSize();
	VECTOR2 mapSize = VECTOR2(MAPSIZE_X / gridSize.x, MAPSIZE_Y / gridSize.y);
	

	lpMap.setUp(VECTOR2(MAPSIZE_X, MAPSIZE_Y), VECTOR2(GRIDSIZE, GRIDSIZE));
	lpMap.ChangeInstanceCnt();
	lpMap.LoadMap(objlist, true);

	startTime = GetNowCount();
	timeUpFlag = false;
	countDownFlag = false;
	countDown = 0;
	return 0;
	return 0;
}

void GameScene::Draw(void)
{
	auto Scr = lpScene.GetScrSize();

	DrawFormatString(600, 0, 0xffff00, "Main");

	//objlist->sort([](Objshared& obj1, Objshared& obj2) {return obj1->GetTypeNum() > obj2->GetTypeNum(); });

	Shared_ObjList tmplist(objlist->size());

	auto typeItr = std::remove_copy_if(objlist->begin(), objlist->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_PREY)); });
	for_each(tmplist.begin(), typeItr, [&](auto &preyType) 
	{
		PLAYER tNum = preyType->GetPlayerNum();
		auto camera = preyType->GetCameraPosition();
	
		lpMap.IndividualsDraw(true,tNum,lpMap.playerCnt,camera);
		lpMap.Draw(false,lpMap.mapScaleCnt,lpMap.playerCnt, tNum,camera);
	});
	lpMap.MapDraw(true);
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Draw();
	}
	if (timeUpFlag)
	{
		DrawGraph(300, 100, itTimeUpImage, true);
	}
	if (countDownFlag)
	{
		DrawGraph(300, 30, countDownImage[countDown], true);
	}

}

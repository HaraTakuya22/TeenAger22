#include <DxLib.h>
#include "Prey.h"
#include "It.h"
#include "Obj.h"
#include "Scene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "ResultScene.h"

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
	// objList‚Ì±¯ÌßÃŞ°Ä
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}

	// ¹Ş°ÑÊß¯ÄŞ‚ÌBack·°‚ğ‰Ÿ‰º ¨ EditScene‚ÉˆÚs
	if (Pad & PAD_INPUT_11)
	{
		return std::make_unique<EditScene>();
	}

	// ¹Ş°ÑÊß¯ÄŞ‚ÌBack·°‚ğ‰Ÿ‰º ¨ EditScene‚ÉˆÚs
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
	//if (GetNowCount() - startTime > 10000)
	//{
	//	return std::make_unique<ResultScene>();
	//}

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
	for (int p = PREY_1; p <= PREY_3; p++)
	{
		preyInstancePos[p] = VECTOR2(GetRand(MAPSIZE_X / GRIDSIZE) * GRIDSIZE, 
									(GetRand(MAPSIZE_Y / GRIDSIZE) * GRIDSIZE) - 40);
		is_Instance[p] = false;
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
		VECTOR2 IndPos = preyType->GetIndividualsMapPos();
		int count = preyType->GetPlayerCnt();
	
	lpMap.IndividualsDraw(true,IndPos,count);
	lpMap.Draw(false,lpMap.mapScaleCnt, IndPos, count);
	});
	
	lpMap.MapDraw(true);
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Draw();
	}
	if(timeUpFlag)
	{
		DrawGraph(300, 100, itTimeUpImage, true);
	}
	if (countDownFlag)
	{
		DrawGraph(300, 30, countDownImage[countDown], true);
	}
}

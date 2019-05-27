#include <DxLib.h>
#include "Obj.h"
#include "Scene.h"
#include "GameScene.h"
#include "EditScene.h"

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
	
	
	ClsDrawScreen();
	Draw();
	ScreenFlip();


	return move(own);
}

int GameScene::Init(void)
{
	if (!objlist)
	{
		objlist = std::make_shared<Shared_ObjList>();
	}

	VECTOR2 gridSize = lpMap.GetGridSize();
	VECTOR2 mapSize = VECTOR2(MAPSIZE_X / gridSize.x, MAPSIZE_Y / gridSize.y);
	// prey‚Ì²İ½Àİ½??
	if (lpMap.player == PLAYER_1)
	{
		lpMap._PreyInstance(objlist, VECTOR2(gridSize.x, gridSize.y),false,1);
	}
	if (lpMap.player == PLAYER_2)
	{
		for (int i = 1; i < 3; i++)
		{
			lpMap._PreyInstance(objlist, VECTOR2(gridSize.x, gridSize.y), false,i);
		}
	}

	lpMap.setUp(VECTOR2(MAPSIZE_X, MAPSIZE_Y), VECTOR2(GRIDSIZE, GRIDSIZE));
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
	
		lpMap.IndividualsDraw(true, IndPos, count);
		lpMap.LoadMap(IndPos, count);
	});
	
	lpMap.MapDraw(true);
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Draw();
	}
}

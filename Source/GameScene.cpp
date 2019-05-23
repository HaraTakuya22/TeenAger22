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
	if (!is_makePrey)
	{
		// prey‚Ì²İ½Àİ½
		if (lpMap.player == PLAYER_1)
		{
			lpMap._PreyInstance(objlist, PREY_1, VECTOR2(GRIDSIZE * 3, GRIDSIZE * 3 + 40));
			is_makePrey = true;
		}
		if (lpMap.player == PLAYER_2)
		{
			lpMap._PreyInstance(objlist, PREY_1, VECTOR2(GRIDSIZE * 3, GRIDSIZE * 3 + 40));
			lpMap._PreyInstance(objlist, PREY_2, VECTOR2(GRIDSIZE * 3, GRIDSIZE * 3 + 40));
			is_makePrey = true;
		}
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
	lpMap.CreateMap();

	is_makePrey = false;
	lpMap.setUp(VECTOR2(MAPSIZE_X, MAPSIZE_Y), VECTOR2(GRIDSIZE, GRIDSIZE));
	return 0;
}

void GameScene::Draw(void)
{
	auto Scr = lpScene.GetScrSize();

	DrawFormatString(600, 0, 0xffff00, "Main");

	Shared_ObjList tmplist(objlist->size());

	auto typeItr = std::remove_copy_if(objlist->begin(), objlist->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_PREY)); });
	for_each(tmplist.begin(), typeItr, [&](auto &preyType) 
	{
		VECTOR2 IndPos = preyType->GetIndividualsMapPos();
		VECTOR2 MapPos = preyType->GetMapPos();
		lpMap.IndividualsDraw(true,MapPos,IndPos);

		lpMap.MapDraw(true);
		DrawFormatString(0, 0, 0xff0000, "No way!");

		lpMap.LoadMap(MapPos);
	});
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Draw();
	}
}

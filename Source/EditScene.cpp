#include "Map.h"
#include "Scene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"


EditScene::EditScene()
{
	Init();
}


EditScene::~EditScene()
{
}

unique_Base EditScene::Update(unique_Base own, const Controller & Controller)
{
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);
	// objList‚Ì±¯ÌßÃŞ°Ä
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}

	// ¹Ş°ÑÊß¯ÄŞ‚ÌStart·°‚ğ‰Ÿ‰º ¨ GameScene‚ÉˆÚs
	if (Pad & PAD_INPUT_12)
	{
		return std::make_unique<GameScene>();
	}

	EditDraw();
	return move(own);
}

int EditScene::Init(void)
{
	if (!objlist)
	{
		objlist = std::make_shared<Shared_ObjList>();
	}
	objlist->clear();
	lpMap.setUp(VECTOR2(SCREENSIZE_X, SCREENSIZE_Y), VECTOR2(GRIDSIZE, GRIDSIZE));
	obj = AddList()(objlist, std::make_unique<EditCursor>(VECTOR2(GRIDSIZE, GRIDSIZE)));
	// Á¯Ìß1–‡1–‡‚ğŠi”[----------------------------------------------------------------
	/*(*obj)->Init("image/map1.png", VECTOR2(3, 2), VECTOR2(GRIDSIZE,GRIDSIZE));
	(*obj)->Init("image/map2.png", VECTOR2(5, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 2));
	(*obj)->Init("image/map3.png", VECTOR2(5, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 3));
	(*obj)->Init("image/map4.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 2, GRIDSIZE * 3));
	(*obj)->Init("image/map5.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 3, GRIDSIZE * 2));
	(*obj)->Init("image/map6.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 3, GRIDSIZE * 3));
	(*obj)->Init("image/map7.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 4));
	(*obj)->Init("image/map8.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 2, GRIDSIZE * 4));*/
	// --------------------------------------------------------------------------------

	return 0;
}

void EditScene::EditDraw(void)
{
	ClsDrawScreen();

	lpMap.CreateIndividualsDisplay();
	lpMap.IndividualsDraw(objlist,false);
	
	lpMap.MapDraw(false);
	lpMap.SetObj();
	//	´ÃŞ¨¯Ä¼°İ‚Ì•`‰æ
	auto itr = objlist->begin();
	(*itr)->Draw();

	ScreenFlip();
}

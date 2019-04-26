#include <DxLib.h>
#include "Scene.h"
#include "GameScene.h"
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
	
	// objList�̱����ް�
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}
	lpMap.MapInit();

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
	return 0;
}

void GameScene::Draw(void)
{
	auto Scr = lpScene.GetScrSize();

	DrawFormatString(600, 0, 0xffff00, "Main");
	lpMap.CreateIndividualsDisplay();
	lpMap.IndividualsDraw(objlist);

	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Draw();
	}
	lpMap.MapDraw();

}

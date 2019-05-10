#include <DxLib.h>
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

	// objList�̱����ް�
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}

	// �ް��߯�ނ�Back�������� �� EditScene�Ɉڍs
	if (Pad & PAD_INPUT_11)
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
	lpMap.setUp(VECTOR2(MAPSIZE_X,MAPSIZE_Y),VECTOR2(GRIDSIZE,GRIDSIZE));
	lpMap.LoadMap();
	return 0;
}

void GameScene::Draw(void)
{
	auto Scr = lpScene.GetScrSize();

	DrawFormatString(600, 0, 0xffff00, "Main");
	lpMap.CreateIndividualsDisplay();
	lpMap.IndividualsDraw(objlist,true);
	lpMap.MapDraw(true);

	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Draw();
	}
	

}

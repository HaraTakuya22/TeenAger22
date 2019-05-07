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
	// objListのｱｯﾌﾟﾃﾞｰﾄ
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}

	// ｹﾞｰﾑﾊﾟｯﾄﾞのStartｷｰを押下 → GameSceneに移行
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
	auto obj = AddList()(objlist, std::make_unique<EditCursor>(VECTOR2(0, 0)));
	(*obj)->Init("image/chis.png", VECTOR2(5, 2), VECTOR2(80, 80));

	return 0;
}

void EditScene::EditDraw(void)
{
	ClsDrawScreen();

	lpMap.CreateIndividualsDisplay();
	lpMap.IndividualsDraw(objlist);
	lpMap.MapDraw(false);
	//	ｴﾃﾞｨｯﾄｼｰﾝ時の描画
	auto itr = objlist->begin();
	(*itr)->Draw();

	ScreenFlip();
}

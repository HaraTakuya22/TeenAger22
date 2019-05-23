#include "Map.h"
#include "Scene.h"
#include "SelectScene.h"
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
	auto input = Controller.GetButtonInfo(KEY_TYPE_NOW);
	auto inputOld = Controller.GetButtonInfo(KEY_TYPE_OLD);
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);
	// objListのｱｯﾌﾟﾃﾞｰﾄ
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}
	Shared_ObjList tmplist(objlist->size());

	auto cursortypeItr = std::remove_copy_if(objlist->begin(), objlist->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_CURSOR)); });
	for_each(tmplist.begin(), cursortypeItr, [&](auto &cursorType)
	{
		auto mapPos = cursorType->GetMapPos();
		lpMap.ChangeEditMapScale(Controller, mapPos);

		//	Sを押したとき、ﾃﾞｰﾀをｾｰﾌﾞする
		if (input[KEY_INPUT_S])
		{
			// save処理(Message表示処理)
			if (MessageBox(NULL, "Do you want to save now??", "Check Dialog.", MB_OKCANCEL) == IDOK)
			{
				lpMap.SaveMap();
			}
		}
	
		//	Lを押したとき、ﾃﾞｰﾀをﾛｰﾄﾞする
		if (input[KEY_INPUT_L])
		{
			// load処理(Message表示処理)
			if (MessageBox(NULL, "Do you want to load now??", "Check Dialog.", MB_OKCANCEL) == IDOK)
			{
				lpMap.LoadMap(mapPos);
			}
		}
	});
	// ｹﾞｰﾑﾊﾟｯﾄﾞのStartｷｰを押下 → GameSceneに移行
	if (Pad & PAD_INPUT_12)
	{
		return std::make_unique<GameScene>();
	}

	// Aﾎﾞﾀﾝを押下かつ拡大していない場合にだけGameSceneに移行
	if (input[KEY_INPUT_X] && !lpMap.Get_isScale())
	{
		return std::make_unique<SelectScene>();
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
	lpMap.player = PLAYER_MAX;
	lpMap.setUp(VECTOR2(MAPSIZE_X, MAPSIZE_Y),VECTOR2(GRIDSIZE, GRIDSIZE));
	obj = AddList()(objlist, std::make_unique<EditCursor>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4),TYPE_NUM::NUM_CURSOR));

	return 0;
}

void EditScene::EditDraw(void)
{
	ClsDrawScreen();

	Shared_ObjList tmplist(objlist->size());

	auto cursorTypeItr = std::remove_copy_if(objlist->begin(), objlist->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_CURSOR)); });
	for_each(tmplist.begin(), cursorTypeItr, [&](auto &cursorType)
	{
		auto cursorTypeNum = cursorType->GetTypeNum();
		auto MapPos = cursorType->GetMapPos();
		auto IndPos = cursorType->GetIndividualsMapPos();
		lpMap.IndividualsDraw(false, MapPos,IndPos);
		lpMap.MapDraw(false);

		lpMap.SetObj(lpMap.mapScaleCnt, true, MapPos);
	});
	//	ｴﾃﾞｨｯﾄｼｰﾝ時の描画
	auto itr = objlist->begin();
	(*itr)->Draw();

	ScreenFlip();
}

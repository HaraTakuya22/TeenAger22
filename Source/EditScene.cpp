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
	lpMap.ChangeEditMapScale(Controller);
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
			lpMap.LoadMap();
		}
	}

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
	lpMap.setUp(VECTOR2(MAPSIZE_X, MAPSIZE_Y),
				VECTOR2(GRIDSIZE, GRIDSIZE),PREY_1);
	obj = AddList()(objlist, std::make_unique<EditCursor>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4)));

	return 0;
}

void EditScene::EditDraw(void)
{
	ClsDrawScreen();
	lpMap.IndividualsDraw(objlist, false);

	//lpMap.CreateIndividualsDisplay();

	lpMap.MapDraw(false);
	lpMap.SetObj(lpMap.blockScaleCnt,true);
	//	ｴﾃﾞｨｯﾄｼｰﾝ時の描画
	auto itr = objlist->begin();
	(*itr)->Draw();

	ScreenFlip();
}

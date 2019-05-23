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
	// objList�̱����ް�
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

		//	S���������Ƃ��A�ް����ނ���
		if (input[KEY_INPUT_S])
		{
			// save����(Message�\������)
			if (MessageBox(NULL, "Do you want to save now??", "Check Dialog.", MB_OKCANCEL) == IDOK)
			{
				lpMap.SaveMap();
			}
		}
	
		//	L���������Ƃ��A�ް���۰�ނ���
		if (input[KEY_INPUT_L])
		{
			// load����(Message�\������)
			if (MessageBox(NULL, "Do you want to load now??", "Check Dialog.", MB_OKCANCEL) == IDOK)
			{
				lpMap.LoadMap(mapPos);
			}
		}
	});
	// �ް��߯�ނ�Start�������� �� GameScene�Ɉڍs
	if (Pad & PAD_INPUT_12)
	{
		return std::make_unique<GameScene>();
	}

	// A���݂��������g�債�Ă��Ȃ��ꍇ�ɂ���GameScene�Ɉڍs
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
	//	��ި�ļ�ݎ��̕`��
	auto itr = objlist->begin();
	(*itr)->Draw();

	ScreenFlip();
}

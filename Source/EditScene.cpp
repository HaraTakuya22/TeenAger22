#include "Map.h"
#include "Scene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"


EditScene::EditScene(void)
{
	Init();
}


EditScene::~EditScene()
{
}

unique_Base EditScene::Update(unique_Base own, const Controller & Controller)
{
	auto input = Controller.GetKeyButtonInfo(KEY_TYPE_NOW);
	auto inputOld = Controller.GetKeyButtonInfo(KEY_TYPE_OLD);
	auto Pad = GetJoypadInputState(DX_INPUT_PAD1);
	// objList�̱����ް�
	for (auto itr = objlist->begin(); itr != objlist->end(); itr++)
	{
		(*itr)->Update(Controller, objlist);
	}
	lpMap.camera[static_cast<int>(PLAYER::CURSOR)].Update(Controller);

	Shared_ObjList tmplist(objlist->size());

	auto cursortypeItr = std::remove_copy_if(objlist->begin(), objlist->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_CURSOR)); });
	for_each(tmplist.begin(), cursortypeItr, [&](auto &cursorType)
	{
		lpMap.ChangeEditMapScale(Controller);
	});
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
				lpMap.LoadMap(objlist,false);
			}
		}
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
	obj = AddList()(objlist, std::make_unique<EditCursor>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4), NUM_CURSOR));
	lpMap.camera.push_back(Camera(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4), VECTOR2(320, 320), VECTOR2(GRIDSIZE, GRIDSIZE), PLAYER::CURSOR));

	
	lpMap.setUp(VECTOR2(MAPSIZE_X, MAPSIZE_Y),VECTOR2(GRIDSIZE, GRIDSIZE));
	lpMap.CreateMap();

	return 0;
}

void EditScene::EditDraw(void)
{
	ClsDrawScreen();


	Shared_ObjList tmplist(objlist->size());

	auto cursorTypeItr = std::remove_copy_if(objlist->begin(), objlist->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_CURSOR)); });
	for_each(tmplist.begin(), cursorTypeItr, [&](auto &cursorType)
	{
		auto tNum = cursorType->GetPlayerNum();
		auto camera = cursorType->GetCameraPosition();

		lpMap.IndividualsDraw(false,tNum,lpMap.playerCnt,camera);
		lpMap.Draw(true, lpMap.mapScaleCnt,lpMap.playerCnt,tNum,camera);
	});
	lpMap.MapDraw(false);

	lpMap.SetObj(lpMap.mapScaleCnt, true,objlist);
	
		//DrawFormatString(200, 200, 0xffffff, "IndPos.x:%d\nIndPos.y:%d", IndPos.x, IndPos.y);
	//	��ި�ļ�ݎ��̕`��
	auto itr = objlist->begin();
	(*itr)->Draw();

	DrawFormatString(500, 500, 0xffffff, "camera.x:%dcamera.y:%d", lpMap.camera[static_cast<int>(PLAYER::CURSOR)].GetCamera().x, lpMap.camera[static_cast<int>(PLAYER::CURSOR)].GetCamera().y);


	ScreenFlip();
}

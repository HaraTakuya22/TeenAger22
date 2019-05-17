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
	lpMap.ChangeEditMapScale(Controller);
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
			lpMap.LoadMap();
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
	//	��ި�ļ�ݎ��̕`��
	auto itr = objlist->begin();
	(*itr)->Draw();

	ScreenFlip();
}

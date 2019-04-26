#include <DxLib.h>
#include "Map.h"
#include "Scene.h"
#include "Prey.h"
#include "Image.h"



void Map::Draw(void)
{
}

void Map::MapDraw(void)
{	
	// ��ʕ���(player�l������)
	switch (player)
	{
	case PLAYER_1:
		// ��د�ނ̕\��
		for (int y = 0; y <= Scr.y; y += GRIDSIZE)
		{
			DrawLine(0, y, Scr.x, y, 0xffffff);
			for (int x = 0; x <= Scr.x; x += GRIDSIZE)
			{



				DrawLine(x, 0, x, Scr.y, 0xffffff);
			}
		}
		// Map����ʉE���ɔz�u
		DrawGraph(Scr.x - (GRIDSIZE * 6), 0, MapWindow, false);
		DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		break;
	case PLAYER_2:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);

		// Map�̔z�u
		DrawGraph(Scr.x / 2 - (MAPWINDOW_SIZE_X / 2), 0, MapWindow, false);
		DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		break;

	case PLAYER_3:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);
		DrawLine(0, Scr.y / 2, Scr.x, Scr.y / 2, 0xffffff);

		// Map�̔z�u
		DrawGraph((Scr.x - (Scr.x / 4)) - (MAPWINDOW_SIZE_X / 2), (Scr.y - (Scr.y / 4)) - (MAPWINDOW_SIZE_Y / 2), MapWindow, false);
		DrawFormatString(Scr.x / 2 + 150, Scr.y / 2 + (((Scr.y / 3) / 2) / 2) + 50, 0xffffff, "Map");

		break;

	default:
		break;
	}

	DrawLine(GRIDSIZE * 9, GRIDSIZE * 3, GRIDSIZE * 9, Scr.y, 0xff00ff);
}

bool Map::SetMapData(VECTOR2 pos,PASSAGE passage)
{
	auto tmp = VECTOR2(pos.x / GRIDSIZE, pos.y / GRIDSIZE);

	passageF[tmp.x * tmp.y] = passage;
	return true;
}

bool Map::Init(void)
{
	Scr = lpScene.GetScrSize();

	// ��ɔp�~�\��(Map������)----------
	PreyWindow = 0;
	MapWindow = 0;

	mapPos = VECTOR2(0, 0);
	MapImage = LoadGraph("MAP/map.png");

	//----------------------------------

	return true;
}

void Map::CreateIndividualsDisplay(void)
{
	// �e��ڲ�l�������ި���ڲ�𐶐�
	switch (player)
	{
	case PLAYER_1:
		if (PreyWindow >= 0)
		{
			PreyWindow = MakeScreen(Scr.x, Scr.y, true);
			SetDrawScreen(PreyWindow);
			DrawBox(0, 0, Scr.x, Scr.y, 0xffffff, false);
			SetDrawScreen(DX_SCREEN_BACK);
		}
		break;

	case PLAYER_2:
		if (PreyWindow >= 0)
		{
			PreyWindow = MakeScreen(Scr.x / 2, Scr.y, true);
			SetDrawScreen(PreyWindow);
			DrawBox(0, 0, Scr.x / 2, Scr.y, 0xffffff, false);
			SetDrawScreen(DX_SCREEN_BACK);
		}
		break;

	case PLAYER_3:
		if (PreyWindow >= 0)
		{
			PreyWindow = MakeScreen(Scr.x / 2, Scr.y / 2, true);
			SetDrawScreen(PreyWindow);
			DrawBox(0, 0, Scr.x / 2, Scr.y / 2, 0xffffff, false);
			SetDrawScreen(DX_SCREEN_BACK);
		}
		break;
	default:

		break;
	}
}

void Map::IndividualsDraw(WeakList weaklist)
{
	// Map��ʕ\��
	if (player == PLAYER_1 || player == PLAYER_2 || player == PLAYER_3)
	{
		if (MapWindow >= 0)
		{
			MapWindow = MakeScreen(MAPWINDOW_SIZE_X, MAPWINDOW_SIZE_Y, true);
			SetDrawScreen(MapWindow);
			DrawBox(0, 0, MAPWINDOW_SIZE_X, MAPWINDOW_SIZE_Y, 0x0000ff, false);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}

	// player1�̉�ʕ\��
	if (player == PLAYER_1)
	{
		// ���ޯ�ޗp-----------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		//---------------------------------------------

		DrawGraph(0, 0, PreyWindow, true);

		// Map(��)�̕\��
		DrawGraph(mapPos.x, mapPos.y, MapImage, true);

		// Prey(��)�̕\��
		//DrawBox(GRIDSIZE * 4,(GRIDSIZE * 4) - 40,(GRIDSIZE * 4) + PREYSIZE_X,(GRIDSIZE * 5), 0xff0000, true);

		// Prey�̲ݽ�ݽ
		AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 5)));
	}

	// player2�̉�ʕ\��
	if (player == PLAYER_2)
	{
		DrawGraph(0, 0, PreyWindow, true);
		DrawGraph(Scr.x / 2, 0, PreyWindow, true);

		// ���ޯ�ޗp--------------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		//------------------------------------------------------------
	}

	// player3�̉�ʕ\��
	if (player == PLAYER_3)
	{
		DrawGraph(0, 0, PreyWindow, true);
		DrawGraph(Scr.x / 2, 0, PreyWindow, true);
		DrawGraph(0, Scr.y / 2, PreyWindow, true);

		// ���ޯ�ޗp------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		DrawFormatString(50, Scr.y / 2 + 50, 0xffffff, "Player3");
		//----------------------------------------------------
	}
}

Map::Map()
{
	Init();
}


Map::~Map()
{
}

#include <DxLib.h>

#include "Map.h"
#include "Scene.h"
#include "Prey.h"
#include "Image.h"



void Map::Draw(void)
{
}

void Map::MapDraw(bool gameF)
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
		if (gameF)
		{
			DrawGraph(Scr.x - (GRIDSIZE * 6), 0, MapWindow, false);
			DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		}
		break;
	case PLAYER_2:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);

		// Map�̔z�u
		if (gameF)
		{
			DrawGraph(Scr.x / 2 - (MAPWINDOW_SIZE_X / 2), 0, MapWindow, false);
			DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		}
		break;

	case PLAYER_3:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);
		DrawLine(0, Scr.y / 2, Scr.x, Scr.y / 2, 0xffffff);

		// Map�̔z�u
		if (gameF)
		{
			DrawGraph((Scr.x - (Scr.x / 4)) - (MAPWINDOW_SIZE_X / 2), (Scr.y - (Scr.y / 4)) - (MAPWINDOW_SIZE_Y / 2), MapWindow, false);
			DrawFormatString(Scr.x / 2 + 150, Scr.y / 2 + (((Scr.y / 3) / 2) / 2) + 50, 0xffffff, "Map");
		}
		break;

	default:
		break;
	}
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/chips.png")[static_cast<int>(id)], true);
			DrawFormatString(x * ChipSize.x, y * ChipSize.y, 0xff0000, "%d", MapData[y][x]);
		}
	}

	DrawLine(GRIDSIZE * 9, GRIDSIZE * 3, GRIDSIZE * 9, Scr.y, 0xff00ff);

	if (!gameF)
	{
		DrawFormatString(0, 0, 0xff0000, "EditMode");
	}
	else
	{
		DrawFormatString(0, 0, 0xff0000, "GameMode");
	}
	
}

//bool Map::CheckPassage(VECTOR2 pos, PASSAGE passage,DIR dir)
//{
//	// �߼޼�݂�Ͻ�ڂŕ\��
//	auto tmp = VECTOR2(pos.x / GRIDSIZE, pos.y / GRIDSIZE);
//	// ��ڲ԰�ׂ̗�����
//	auto NextPos = [&](DIR dir) {
//		VECTOR2 nextpos;
//		switch (dir)
//		{
//			// ���̏ꍇ
//		case DIR_LEFT:
//			nextpos = { pos.x + PREYSIZE_X,0 };
//			break;
//
//			// �E�̏ꍇ
//		case DIR_RIGHT:
//			nextpos = { pos.x + PREYSIZE_X,0 };
//			break;
//
//			// ��̏ꍇ
//		case DIR_UP:
//			nextpos = { 0,pos.y + PREYSIZE_Y };
//			break;
//
//			// ���̏ꍇ
//		case DIR_DOWN:
//			nextpos = { 0,pos.y + PREYSIZE_Y };
//			break;
//
//		default:
//			break;
//		};
//		return pos + nextpos;
//	};
//	// �悪�ǂ�������
//	if (NextPos(dir) == passage)
//	{
//		return false;
//	}
//	return true;
//}

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

struct SizeCheck
{
	bool operator()(const VECTOR2 &tmpPos, const VECTOR2 &MapSize) {
		//ϯ�ߓ��ł���΁A�`��OK
		if ((tmpPos.x < 0) || (tmpPos.y < 0) || (MapSize.x <= tmpPos.x) || (MapSize.y <= tmpPos.y))
		{
			return false;
		}
		return true;
	}
};

void Map::setUp(const VECTOR2& size, const VECTOR2& chipSize)
{
	lpImage.GetID("image/chips.png", VECTOR2(5, 2), VECTOR2(80, 80));

	MapSize = VECTOR2(size.x / chipSize.x, size.y / chipSize.y);

	this->ChipSize = chipSize;

	auto createMap = [=](auto& base, auto& frontMap, auto initNum)
	{
		base.resize(MapSize.x * MapSize.y);
		frontMap.resize(MapSize.y);

		//���Ԋu���߲�����ڽ�����Ă���(�A��)��
		for (int cnt = 0; cnt < frontMap.size(); cnt++)
		{
			frontMap[cnt] = &base[MapSize.x * cnt];			//�摜�ް��̑S�̂���
		}
		//�S�ĉ񂵂���mapnon�ŏ��������Ă����B
		for (int j = 0; j < base.size(); j++)
		{
			base[j] = initNum;
		}
	};
	createMap(BaseMap, MapData, objID::ID_NON);
}

bool Map::setMapData(const VECTOR2 & pos, objID id)
{
	return setData(MapData,pos,id);
}

// Map���ID���𑼂ɓn���Ă�����
objID Map::GetMapData(const VECTOR2 & pos)
{
	return GetData(MapData,pos,objID::ID_9);
}

template<typename MapType, typename IDType>
bool Map::setData(MapType maptype, const VECTOR2 & pos, IDType id)
{
	VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x , pos.y / ChipSize.y );

	// Map���łȂ��ꍇ�͕`�悵�Ȃ�
	//if (!SizeCheck()(tmp, MapSize));
	/*{
		return false;
	}*/
	// Map���̏ꍇ�͕`��OK
	maptype[tmp.y][tmp.x] = id;
	_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", pos.x, pos.y, id);
	return true;
}

template<typename MapType, typename IDType>
IDType Map::GetData(MapType maptype, const VECTOR2 & pos, IDType defID)
{
	VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x, pos.y / ChipSize.y);

	SizeCheck sizeCheck;

	if (!sizeCheck(tmp,MapSize))
	{
		return defID;
	}
	return maptype[tmp.y][tmp.x];
}

Map::Map()
{
	Init();
}


Map::~Map()
{
}

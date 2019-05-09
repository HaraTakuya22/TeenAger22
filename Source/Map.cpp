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
	// 画面分割(player人数毎に)
	switch (player)
	{
	case PLAYER_1:
		// ｸﾞﾘｯﾄﾞの表示
		for (int y = 0; y <= Scr.y; y += GRIDSIZE)
		{
			DrawLine(0, y, Scr.x, y, 0xffffff);
			for (int x = 0; x <= Scr.x; x += GRIDSIZE)
			{
				DrawLine(x, 0, x, Scr.y, 0xffffff);
			}
		}
		// Mapを画面右下に配置
		if (gameF)
		{
			DrawGraph(Scr.x - (GRIDSIZE * 6), 0, MapWindow, false);
			DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		}
		break;
	case PLAYER_2:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);

		// Mapの配置
		if (gameF)
		{
			DrawGraph(Scr.x / 2 - (MAPWINDOW_SIZE_X / 2), 0, MapWindow, false);
			DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		}
		break;

	case PLAYER_3:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);
		DrawLine(0, Scr.y / 2, Scr.x, Scr.y / 2, 0xffffff);

		// Mapの配置
		if (gameF)
		{
			DrawGraph((Scr.x - (Scr.x / 4)) - (MAPWINDOW_SIZE_X / 2), (Scr.y - (Scr.y / 4)) - (MAPWINDOW_SIZE_Y / 2), MapWindow, false);
			DrawFormatString(Scr.x / 2 + 150, Scr.y / 2 + (((Scr.y / 3) / 2) / 2) + 50, 0xffffff, "Map");
		}
		break;

	default:
		break;
	}
	/*for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true);
			DrawFormatString(x * ChipSize.x, y * ChipSize.y, 0xff0000, "%d", MapData[y][x]);
		}
	}*/

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
//	// ﾎﾟｼﾞｼｮﾝをﾏｽ目で表現
//	auto tmp = VECTOR2(pos.x / GRIDSIZE, pos.y / GRIDSIZE);
//	// ﾌﾟﾚｲﾔｰの隣を見る
//	auto NextPos = [&](DIR dir) {
//		VECTOR2 nextpos;
//		switch (dir)
//		{
//			// 左の場合
//		case DIR_LEFT:
//			nextpos = { pos.x + PREYSIZE_X,0 };
//			break;
//
//			// 右の場合
//		case DIR_RIGHT:
//			nextpos = { pos.x + PREYSIZE_X,0 };
//			break;
//
//			// 上の場合
//		case DIR_UP:
//			nextpos = { 0,pos.y + PREYSIZE_Y };
//			break;
//
//			// 下の場合
//		case DIR_DOWN:
//			nextpos = { 0,pos.y + PREYSIZE_Y };
//			break;
//
//		default:
//			break;
//		};
//		return pos + nextpos;
//	};
//	// 先が壁だったら
//	if (NextPos(dir) == passage)
//	{
//		return false;
//	}
//	return true;
//}

bool Map::Init(void)
{
	Scr = lpScene.GetScrSize();

	// 後に廃止予定(Map完成後)----------
	PreyWindow = 0;
	MapWindow = 0;

	mapPos = VECTOR2(0, 0);
	MapImage = LoadGraph("MAP/map_new.png");

	//----------------------------------

	is_makePrey = false;

	return true;
}

void Map::CreateIndividualsDisplay(void)
{
	// 各ﾌﾟﾚｲ人数毎にﾃﾞｨｽﾌﾟﾚｲを生成
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

void Map::IndividualsDraw(WeakList weaklist,bool gameF)
{
	// Map画面表示
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

	// player1の画面表示
	if (player == PLAYER_1)
	{
		// ﾃﾞﾊﾞｯｸﾞ用-----------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		//---------------------------------------------

		DrawGraph(0, 0, PreyWindow, true);

		// Mapの表示
		DrawRectGraph(mapPos.x, mapPos.y,0,0,MAPSIZE_X,MAPSIZE_Y, MapImage, true,false);

		// Prey(仮)の表示
		//DrawBox(GRIDSIZE * 4,(GRIDSIZE * 4) - 40,(GRIDSIZE * 4) + PREYSIZE_X,(GRIDSIZE * 5), 0xff0000, true);

		// Preyのｲﾝｽﾀﾝｽ(GameSceneのみ)
		if (gameF && !is_makePrey)
		{
			AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4 - 40)));
			is_makePrey = true;
		}
	}

	// player2の画面表示
	if (player == PLAYER_2)
	{
		DrawGraph(0, 0, PreyWindow, true);
		DrawGraph(Scr.x / 2, 0, PreyWindow, true);

		// ﾃﾞﾊﾞｯｸﾞ用--------------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		//------------------------------------------------------------
	}

	// player3の画面表示
	if (player == PLAYER_3)
	{
		DrawGraph(0, 0, PreyWindow, true);
		DrawGraph(Scr.x / 2, 0, PreyWindow, true);
		DrawGraph(0, Scr.y / 2, PreyWindow, true);

		// ﾃﾞﾊﾞｯｸﾞ用------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		DrawFormatString(50, Scr.y / 2 + 50, 0xffffff, "Player3");
		//----------------------------------------------------
	}
}

struct SetCheck
{
	bool operator()(const VECTOR2 &tmpPos, const VECTOR2 &MapSize) {
		//ﾏｯﾌﾟ内であれば、描画OK
		if ((tmpPos.x < 1) || (tmpPos.y < 1) || ((MapSize.x / GRIDSIZE) <= tmpPos.x) || ((MapSize.y / GRIDSIZE) <= tmpPos.y))
		{
			return false;
		}
		return true;
	}
};

void Map::setUp(const VECTOR2& size, const VECTOR2& chipSize)
{

	// ﾏｯﾌﾟﾁｯﾌﾟのｸﾞﾗﾌｨｯｸの読み込み-------------------------------------------------------
	lpImage.GetID("image/map1.png", VECTOR2(3, 2), VECTOR2(GRIDSIZE,GRIDSIZE));
	lpImage.GetID("image/map2.png", VECTOR2(5, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 2));
	lpImage.GetID("image/map3.png", VECTOR2(5, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 3));
	lpImage.GetID("image/map4.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 2, GRIDSIZE * 3));
	lpImage.GetID("image/map5.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 3, GRIDSIZE * 2));
	lpImage.GetID("image/map6.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 3, GRIDSIZE * 3));
	lpImage.GetID("image/map7.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 4));
	lpImage.GetID("image/map8.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 2, GRIDSIZE * 4));
	// ----------------------------------------------------------------------------------

	MapSize = VECTOR2(size.x / chipSize.x, size.y / chipSize.y);

	this->ChipSize = chipSize;

	auto createMap = [=](auto& base, auto& frontMap, auto initNum)
	{
		base.resize(MapSize.x * MapSize.y);
		frontMap.resize(MapSize.y);

		//一定間隔のﾎﾟｲﾝﾀｱﾄﾞﾚｽを入れていく(連結)↓
		for (int cnt = 0; cnt < frontMap.size(); cnt++)
		{
			frontMap[cnt] = &base[MapSize.x * cnt];			//画像ﾃﾞｰﾀの全体を回す
		}
		//全て回したらmapnonで初期化しておく。
		for (int j = 0; j < base.size(); j++)
		{
			base[j] = initNum;
		}
	};
	createMap(BaseMap, MapData, objID::NON);
}

bool Map::setMapData(const VECTOR2 & pos, objID id)
{
	return setData(MapData,pos,id);
}

// Map上のID情報を他に渡してあげる
objID Map::GetMapData(const VECTOR2 & pos)
{
	return GetData(MapData,pos,objID::FLOOR);
}

template<typename MapType, typename IDType>
bool Map::setData(MapType maptype, const VECTOR2 & pos, IDType id)
{
	//ChangeChipSize();
	VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x , pos.y / ChipSize.y );

	// Map内でない場合は描画しない
	/*if (!SetCheck()(tmp, MapSize));
	{
		return false;
	}*/
	// Map内の場合は描画OK
	maptype[tmp.y][tmp.x] = id;
	_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", pos.x, pos.y, id);
	return true;
}

template<typename MapType, typename IDType>
IDType Map::GetData(MapType maptype, const VECTOR2 & pos, IDType defID)
{
	VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x, pos.y / ChipSize.y);

	SetCheck setCheck;

	if (!setCheck(tmp,MapSize))
	{
		return defID;
	}
	return maptype[tmp.y][tmp.x];
}

/*bool Map::ChangeChipSize(void)
{
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			VECTOR2 changedSize;
			switch (id)
			{
			case objID::FLOOR:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;
			case objID::WALL:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;

			case objID::TABLE:
				changedSize.x = GRIDSIZE * 2;
				changedSize.y = GRIDSIZE * 4;
				break;

			case objID::SUBTABLE:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 4;
				break;

			case objID::SUBMONITOR:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::MONITOR:
				changedSize.x = GRIDSIZE * 3;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::BED:
				changedSize.x = GRIDSIZE * 2;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::VASE_1:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 2;
				break;

			case objID::VASE_2:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 2;
				break;

			case objID::DESK:
				changedSize.x = GRIDSIZE * 3;
				changedSize.y = GRIDSIZE * 2;
				break;

			case objID::MIRRORTABLE:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::FACE:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::KITCHIN_1:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::KITCHIN_2:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 3;
				break;

			case objID::BOOKSHELF:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 2;
				break;

			case objID::DRAWER:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 2;
				break;

			case objID::LOCKER:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE * 2;
				break;

			case objID::CHAIR_1:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;

			case objID::CHAIR_2:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;

			case objID::CHAIR_3:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;

			case objID::CHAIR_4:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;

			case objID::NON:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;

			default:
				changedSize.x = GRIDSIZE;
				changedSize.y = GRIDSIZE;
				break;
			}
		}
	}
	return true;
}*/

bool Map::SetObj(void)
{
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			switch (id)
			{
			case objID::FLOOR:
			case objID::WALL:	
			case objID::CHAIR_1:	
			case objID::CHAIR_2:	
			case objID::CHAIR_3:
			case objID::CHAIR_4:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
				break;
			case objID::BOOKSHELF:
			case objID::DRAWER:
			case objID::LOCKER:
			case objID::VASE_1:
			case objID::VASE_2:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map2.png")[static_cast<int>(id) - 7], true);
				break;
			case objID::MIRRORTABLE:
			case objID::FACE:
			case objID::KITCHIN_1:
			case objID::KITCHIN_2:
			case objID::S_MONITOR:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map3.png")[static_cast<int>(id) - 11], true);
				break;
			case objID::BED:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map4.png")[0], true);
				break;
			case objID::DESK:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map5.png")[0], true);
				break;
			case objID::MONITOR:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map6.png")[0], true);
				break;
			case objID::S_TABLE:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map7.png")[0], true);
				break;
			case objID::TABLE:
				DrawGraph(x * ChipSize.x, y * ChipSize.y, lpImage.GetID("image/map8.png")[0], true);
				break;
			default:
				break;
			}
		}
	}
	return true;
}

Map::Map()
{
	Init();
}


Map::~Map()
{
}
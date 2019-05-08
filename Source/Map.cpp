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
	MapImage = LoadGraph("MAP/map.png");

	//----------------------------------

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

void Map::IndividualsDraw(WeakList weaklist)
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
		DrawRectGraph(mapPos.x, mapPos.y,0,0,SCREENSIZE_X * 4,(SCREENSIZE_Y * 4) + (GRIDSIZE * 3), MapImage, true,false);

		// Prey(仮)の表示
		//DrawBox(GRIDSIZE * 4,(GRIDSIZE * 4) - 40,(GRIDSIZE * 4) + PREYSIZE_X,(GRIDSIZE * 5), 0xff0000, true);

		// Preyのｲﾝｽﾀﾝｽ
		AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 5)));
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

struct SizeCheck
{
	bool operator()(const VECTOR2 &tmpPos, const VECTOR2 &MapSize) {
		//ﾏｯﾌﾟ内であれば、描画OK
		if ((tmpPos.x < 0) || (tmpPos.y < 0) || (MapSize.x <= tmpPos.x) || (MapSize.y <= tmpPos.y))
		{
			return false;
		}
		return true;
	}
};

void Map::setUp(const VECTOR2& size, const VECTOR2& chipSize)
{
	ChangeCursorShape();
	lpImage.GetID("image/mapblock.png", VECTOR2(9, 8), VECTOR2(cursorShape.x, cursorShape.y));

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

bool Map::SetObj(WeakList objlist)
{
	Shared_ObjList tmplist(objlist.lock()->size());
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			auto Cursor = std::remove_copy_if(objlist.lock()->begin(), objlist.lock()->end(), tmplist.begin(), [](Objshared& obj) {return !(obj->GetType(TYPE_CURSOR)); });
			for_each(tmplist.begin(), Cursor, [&](auto &cursor) {
				VECTOR2 cursorPos = cursor->GetPos();
				objID id = MapData[y][x];
				switch (id)
				{
				case objID::FLOOR:
					DrawRectGraph(cursorPos.x, cursorPos.y, 0, 0, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::WALL:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE, 0, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::TABLE:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 2, 0, GRIDSIZE * 2, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::SUBTABLE:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 4, 0, GRIDSIZE, GRIDSIZE * 4, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::SUBMONITOR:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 5, 0, GRIDSIZE, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::MONITOR:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 6, 0, GRIDSIZE * 3, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::BED:
					DrawRectGraph(cursorPos.x, cursorPos.y, 0, GRIDSIZE, GRIDSIZE * 2, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::VASE_1:
					DrawRectGraph(cursorPos.x, cursorPos.y, 0, GRIDSIZE * 4, GRIDSIZE, GRIDSIZE * 2, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::VASE_2:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE, GRIDSIZE * 4, GRIDSIZE, GRIDSIZE * 2, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::DESK:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 2, GRIDSIZE * 4, GRIDSIZE * 3, GRIDSIZE * 2, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::MIRRORTABLE:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 5, GRIDSIZE * 3, GRIDSIZE, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::FACE:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 6, GRIDSIZE * 3, GRIDSIZE, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::KITCHIN_1:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 7, GRIDSIZE * 3, GRIDSIZE, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::KITCHIN_2:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 8, GRIDSIZE * 3, GRIDSIZE, GRIDSIZE * 3, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::BOOKSHELF:
					DrawRectGraph(cursorPos.x, cursorPos.y, 0, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE * 2, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::DRAWER:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE * 2, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::LOCKER:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 2, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE * 2, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::CHAIR_1:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 3, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::CHAIR_2:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 4, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::CHAIR_3:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 5, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::CHAIR_4:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 6, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				case objID::NON:
					DrawRectGraph(cursorPos.x, cursorPos.y, GRIDSIZE * 7, GRIDSIZE * 6, GRIDSIZE, GRIDSIZE, lpImage.GetID("image/mapblock.png")[static_cast<int>(id)], true, true);
					break;
				default:
					break;
				}
			});
		}
	}

	return true;
}

template<typename MapType, typename IDType>
bool Map::setData(MapType maptype, const VECTOR2 & pos, IDType id)
{
	VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x , pos.y / ChipSize.y );

	// Map内でない場合は描画しない
	//if (!SizeCheck()(tmp, MapSize));
	/*{
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

bool Map::ChangeCursorShape(void)
{
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
				objID id = MapData[y][x];
				switch (id)
				{
				case objID::FLOOR:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				case objID::WALL:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				case objID::TABLE:
					cursorShape.x = GRIDSIZE * 2;
					cursorShape.y = GRIDSIZE * 4;
					break;
				case objID::SUBTABLE:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 4;
					break;
				case objID::SUBMONITOR:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::MONITOR:
					cursorShape.x = GRIDSIZE * 3;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::BED:
					cursorShape.x = GRIDSIZE * 2;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::VASE_1:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 2;
					break;
				case objID::VASE_2:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 2;
					break;
				case objID::DESK:
					cursorShape.x = GRIDSIZE * 3;
					cursorShape.y = GRIDSIZE * 2;
					break;
				case objID::MIRRORTABLE:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::FACE:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::KITCHIN_1:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::KITCHIN_2:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 3;
					break;
				case objID::BOOKSHELF:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 2;
					break;
				case objID::DRAWER:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 2;
					break;
				case objID::LOCKER:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE * 2;
					break;
				case objID::CHAIR_1:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				case objID::CHAIR_2:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				case objID::CHAIR_3:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				case objID::CHAIR_4:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				case objID::NON:
					cursorShape.x = GRIDSIZE;
					cursorShape.y = GRIDSIZE;
					break;
				default:
					break;
				}
		}
	}
	return true;
}

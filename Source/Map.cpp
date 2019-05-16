#include <DxLib.h>

#include "Map.h"
#include "Scene.h"
#include "Prey.h"
#include "Image.h"

struct DataHeader {
	char fileID[13];		//ﾌｧｲﾙのID
	char VerID;				//ﾊﾞｰｼﾞｮﾝ番号
	char reserve1[2];		//予約領域
	int	 SizeX;				//ﾏｯﾌﾟのﾏｽ目数X
	int  SizeY;				//ﾏｯﾌﾟのﾏｽ目数Y
	char reserve2[3];		//予約領域
	char sum;				//sum値
};

#define SAVE_FILE_ID		"saveFile"
#define SAVE_FILE_VER_ID	0x01

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
		if (!is_scale)
		{
			for (int y = 0; y <= Scr.y; y += GRIDSIZE)
			{
				DrawLine(0, y, Scr.x, y, 0xffffff);
				for (int x = 0; x <= Scr.x; x += GRIDSIZE)
				{
					DrawLine(x, 0, x, Scr.y, 0xffffff);
				}
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
	mapAllwindow = 0;
	preyWindow = 0;
	MapWindow = 0;

	cameraPos = { 320,320 };

	scaleCnt = { 1,1 };
	gameWindowScale = { 0,0 };

	is_scale = false;

	is_mapCreate = false;
	is_preyWindowCreate = false;

	mapPos = VECTOR2(0, 0);
	MapImage = LoadGraph("MAP/map_new.png");

	//----------------------------------
	return true;
}

void Map::CreateIndividualsDisplay(void)
{
	// Mapの表示
	// ﾏｯﾌﾟ全体の画像の生成
	if (mapAllwindow >= 0 && !is_mapCreate)
	{
		mapAllwindow = MakeScreen(MAPSIZE_X, MAPSIZE_Y, true);
		SetDrawScreen(mapAllwindow);
		DrawGraph(0,0, MapImage, true);
		SetDrawScreen(DX_SCREEN_BACK);

		is_mapCreate = true;
	}

	// ﾏｯﾌﾟ全体の画像を基に各ﾌﾟﾚｲﾔｰのｳｨﾝﾄﾞｳのﾎﾟｼﾞｼｮﾝ毎に描画する画像の生成
	if (preyWindow >= 0 && !is_preyWindowCreate)
	{
		preyWindow = MakeScreen(MAPSIZE_X, MAPSIZE_Y, true);
		SetDrawScreen(preyWindow);
		DrawRectGraph(0,0, individualsMapPos.x, individualsMapPos.y, MAPSIZE_X, MAPSIZE_Y, mapAllwindow, true, false);
		SetDrawScreen(DX_SCREEN_BACK);

		is_preyWindowCreate = true;
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
		DrawFormatString(0, 100, 0xff0000, "ind_map.x:%d\nind_map.y;%d", individualsMapPos.x, individualsMapPos.y);
		//---------------------------------------------
		//DrawRectGraph(mapPos.x, mapPos.y,0,0,MAPSIZE_X / scaleCnt,MAPSIZE_Y / scaleCnt, MapImage, true,false);

		DrawExtendGraph(mapPos.x, mapPos.y,(MAPSIZE_X / scaleCnt.x) + mapPos.x,(MAPSIZE_Y / scaleCnt.y) + mapPos.y, preyWindow, true);
		// Preyのｲﾝｽﾀﾝｽ(GameSceneのみ)
		if (gameF && !is_makePrey)
		{
			AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4 - 40),PREY_1));
			is_makePrey = true;
		}
	}

	// player2の画面表示
	if (player == PLAYER_2)
	{
		for (int windowsNum = 0; windowsNum < 2; windowsNum++)
		{
			DrawExtendGraph(mapPos.x + (Scr.x * windowsNum), mapPos.y + (Scr.y * windowsNum), 
							(MAPSIZE_X / scaleCnt.x) + mapPos.x + (Scr.x * windowsNum), (MAPSIZE_Y / scaleCnt.y) + mapPos.y + (Scr.y * windowsNum),
							preyWindow, true);
			// Preyのｲﾝｽﾀﾝｽ(GameSceneのみ)
			if (gameF && !is_makePrey)
			{
				AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4 - 40), PREY_1));
				AddList()(weaklist, std::make_unique<Prey>(VECTOR2((GRIDSIZE * 4) + (mapPos.x + (Scr.x * windowsNum)), (GRIDSIZE * 4 - 40) + (mapPos.y + (Scr.y * windowsNum))),PREY_2));

				is_makePrey = true;
			}
		}
	}

	// player3の画面表示
	if (player == PLAYER_3)
	{
		DrawGraph(0, 0, mapAllwindow, true);
		DrawGraph(Scr.x / 2, 0, mapAllwindow, true);
		DrawGraph(0, Scr.y / 2, mapAllwindow, true);

		// ﾃﾞﾊﾞｯｸﾞ用------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		DrawFormatString(50, Scr.y / 2 + 50, 0xffffff, "Player3");
		//----------------------------------------------------
	}
	Shared_ObjList tmplist(weaklist.lock()->size());

	if (!gameF)
	{
		DrawExtendGraph(mapPos.x, mapPos.y, mapPos.x + (MAPSIZE_X / scaleCnt.x), mapPos.y + (MAPSIZE_Y / scaleCnt.y), MapImage, true);
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

	this->ChipSize = chipSize;

	MapSize = VECTOR2(size.x / chipSize.x, size.y / chipSize.y);

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

bool Map::SaveMap(void)
{
	DataHeader expData = { SAVE_FILE_ID ,SAVE_FILE_VER_ID ,{ 0,0 },MapSize.x,MapSize.y ,{ 0,0,0 },0xff };

	// sum値
	int sumValue = 0;
	//sum値の計算
	for (auto data : BaseMap)
	{
		sumValue += (int)data;
	}

	expData.sum = (char)sumValue;

	FILE *file;
	fopen_s(&file, "MapData/SaveData.map", "wb");				//開く
	fwrite(&expData, sizeof(expData), 1, file);				//書き込み
															//↓map上にﾌﾞﾛｯｸをどこに配置したかのﾃﾞｰﾀ
	fwrite(BaseMap.data(), sizeof(objID) * BaseMap.size(), 1, file);		//map_b_data.data()←生のﾎﾟｲﾝﾀ	fwrite(書き込みたいﾃﾞｰﾀが入っている先頭ﾎﾟｲﾝﾀ,渡すﾃﾞｰﾀのﾊﾞｲﾄ数,最小単位のﾃﾞｰﾀの塊を何回書き込むか,書き込むべきﾌｧｲﾙのﾎﾟｲﾝﾀ)
																				//map_b_data.size()で書いた方が絶対変わらない値なので、安全。
																				//どちらでも記述OK
																				//fwrite(&map_b_data[0], sizeof(map_b_data[0]), 1, file);
	fclose(file);											//閉じる
	return false;
}

bool Map::LoadMap(void)
{
	FILE* file;
	DataHeader expData;
	fopen_s(&file, "MapData/SaveData.map", "rb");		//	開く
	fread(&expData, sizeof(expData), 1, file);		//	読み込む
													//ﾍｯﾀﾞｰのｻｲｽﾞ情報を元にmap_b_dataのｻｲｽﾞをﾘｻｲｽﾞする。//map_b_dataを読み込むまでに一番最速且つ最遅。
	BaseMap.resize(expData.SizeX * expData.SizeY);
	fread(BaseMap.data(), sizeof(objID) * BaseMap.size(), 1, file);//	読み込む
	fclose(file);	//	閉じる

	// isCmp : 比較するﾌﾗｸﾞ
	bool isCmp = true;
	if ((std::string)expData.fileID != SAVE_FILE_ID)
	{
		isCmp = false;
	}
	//ﾍｯﾀﾞｰのﾊﾞｰｼﾞｮﾝ番号と内部で持っている番号を比べる。
	if (expData.VerID != SAVE_FILE_VER_ID)
	{
		isCmp = false;
	}
	//sum値とﾍｯﾀﾞｰの値を比べて違ったら、ﾃﾞｰﾀをｸﾘｱする。
	int SumValue = 0;

	//取得した値をSumに入れていき、どんどん加算していく。
	for (auto data : BaseMap)
	{
		SumValue += (int)data;
	}

	//Sumの値と元の値が違うのであれば、falseに。
	if (expData.sum != (char)SumValue)
	{
		isCmp = false;
	}
	if (!isCmp)
	{
		for (int j = 0; j < BaseMap.size(); j++)
		{
			BaseMap[j] = objID::NON;
		}
		//auto参照にすることでmap_b_data全体を見てるということになる
		//値渡しにするとmap_b_dataを見ることにはならない。
		for (auto &data : BaseMap)
		{
			data = objID::NON;
		}
	}
	//isCmp == true →　正しくloadされたとき
	if (isCmp)
	{
		SetObj(scaleCnt,false);
	}

	return isCmp;
}

template<typename MapType, typename IDType>
bool Map::setData(MapType maptype, const VECTOR2 & pos, IDType id)
{
	if (!is_scale)
	{
		//ChangeChipSize();
		VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x, pos.y / ChipSize.y);

		// ＊ｾｯﾄしたﾁｯﾌﾟのﾎﾟｼﾞｼｮﾝ情報をそのまま全体のﾏｯﾌﾟに格納
		// ﾏｯﾌﾟの移動と共にﾁｯﾌﾟも動かさないといけないので
		//setPos = tmp;
		// Map内でない場合は描画しない
		/*if (!SetCheck()(tmp, MapSize));
		{
			return false;
		}*/
		// Map内の場合は描画OK
		//maptype[setPos.y][setPos.x] = maptype[tmp.y][tmp.x];

		maptype[tmp.y][tmp.x] = id;
	}
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

VECTOR2 Map::MapCalcPos(VECTOR2 c_pos,VECTOR2 scroll)
{
	mapPos = scroll - c_pos;
	return mapPos;
}

VECTOR2& Map::IndividualsMapCalcPos(VECTOR2 pos,VECTOR2 camera)
{
	
	individualsMapPos = pos - camera;
	return individualsMapPos;
}

bool Map::SetObj(VECTOR2 scale,bool is_edit)
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
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + (ChipSize.y / scale.y)) + mapPos.y,
							lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + (ChipSize.y / scale.y)) + mapPos.y,
						lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);

				}
				break;
			case objID::BOOKSHELF:
			case objID::DRAWER:
			case objID::LOCKER:
			case objID::VASE_1:
			case objID::VASE_2:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map2.png")[static_cast<int>(id) - 6], true);
					}
					else
					{
						DrawGraph((x * ChipSize.x) + mapPos.x, (y * ChipSize.y) + mapPos.y, lpImage.GetID("image/map2.png")[static_cast<int>(id) - 6], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map2.png")[static_cast<int>(id) - 6], true);
				}
				break;
			case objID::MIRRORTABLE:
			case objID::FACE:
			case objID::KITCHIN_1:
			case objID::KITCHIN_2:
			case objID::S_MONITOR:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map3.png")[static_cast<int>(id) - 11], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map3.png")[static_cast<int>(id) - 11], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map3.png")[static_cast<int>(id) - 11], true);
				}
				break;
			case objID::BED:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map4.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map4.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map4.png")[0], true);
				}
				break;
			case objID::DESK:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map5.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map5.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map5.png")[0], true);
				}
				break;
				
			case objID::MONITOR:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map6.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map6.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map6.png")[0], true);
				}
				break;
			case objID::S_TABLE:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map7.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map7.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map7.png")[0], true);
				}
				break;
			case objID::TABLE:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) + mapPos.y,
							lpImage.GetID("image/map8.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) + mapPos.x, (y * (ChipSize.y * scale.y)) + mapPos.y, lpImage.GetID("image/map8.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) + mapPos.y,
						lpImage.GetID("image/map8.png")[0], true);
				}
				break;
			default:
				break;
			}
			if (!is_scale)
			{
				DrawFormatString((x * ChipSize.x) + mapPos.x, (y * ChipSize.y) + mapPos.y, 0xff0000, "x:%d\ny:%d\n%d", x, y, id);
			}
		}
	}
	return true;
}

bool Map::ChangeMapScale(bool editF,Controller ctrl)
{
	auto cntNow = ctrl.GetButtonInfo(KEY_TYPE_NOW);
	auto cntOld = ctrl.GetButtonInfo(KEY_TYPE_OLD);
	if (editF)
	{
		if (cntNow[KEY_INPUT_COMMA] & ~cntOld[KEY_INPUT_COMMA]
			&& (scaleCnt.x == 1 && scaleCnt.y == 1))
		{
			mapPos = { 0,0 };

			scaleCnt.x *= 4;
			scaleCnt.y *= 4;
			is_scale = true;
		}
		if (cntNow[KEY_INPUT_PERIOD] & ~cntOld[KEY_INPUT_PERIOD]
			&& (scaleCnt.x == 4 && scaleCnt.y == 4))
		{
			scaleCnt.x /= 4;
			scaleCnt.y /= 4;
			is_scale = false;
		}
	}
	else
	{
		switch (player)
		{
		case PLAYER_1:
			scaleCnt.x = 1;
			scaleCnt.y = 1;
			break;
		case PLAYER_2:
			scaleCnt.x = 1;
			scaleCnt.y = 1;
			break;
		case PLAYER_3:
			scaleCnt.x = 2;
			scaleCnt.y = 2;
			break;
		default:
			break;
		}
	}

	
	return true;
}

Map::Map()
{
	Init();

	is_makePrey = false;
}


Map::~Map()
{
}
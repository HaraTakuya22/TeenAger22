#include <DxLib.h>

#include "Camera.h"

#include "Map.h"
#include "Scene.h"
#include "Image.h"
#include "Prey.h"
#include "NUM_TYPE.h"


using namespace std;

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

void Map::Draw(bool is_edit,VECTOR2 scale,int pCnt,PLAYER tNum,VECTOR2 c_pos)
{
	//ChangeInstanceCnt();]
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			VECTOR2 objPos = VECTOR2((Scr.x / 2 * ((int)tNum - 1)) + (x * ChipSize.x) - c_pos.x, (y * ChipSize.y) - c_pos.y);

			switch (id)
			{
			case objID::PLAYER1:

			case objID::PLAYER2:

			case objID::PLAYER3:

				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map1.png")[static_cast<int>(0)], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map1.png")[static_cast<int>(0)], true);
					}
				}
				else
				{

				}

				break;
			case objID::WALL:
			case objID::CHAIR_1:
			case objID::CHAIR_2:
			case objID::CHAIR_3:
			case objID::CHAIR_4:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (camera[static_cast<int>(tNum)].GetCamera().y / scale.y),
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (camera[static_cast<int>(tNum)].GetCamera().x / scale.x), (((y * (ChipSize.y / scale.y))) + (ChipSize.y / scale.y)) - (camera[static_cast<int>(tNum)].GetCamera().y / scale.y),
							lpImage.GetID("image/map1.png")[static_cast<int>(id - 2)], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map1.png")[static_cast<int>(id - 2)], true);
					}
				}
				else
				{
					if (playerCnt == 1 || playerCnt == 2)
					{
						if ((pCnt == 1 && objPos.x <= Scr.x / scale.x) || (pCnt == 2 && objPos.x >= Scr.x / scale.x))
						{
							DrawGraph(objPos.x, objPos.y, lpImage.GetID("image/map1.png")[static_cast<int>(id - 2)], true);
						}
					}
				}
				break;
			case objID::BOOKSHELF:
			case objID::LOCKER:
			case objID::VASE_1:
			case objID::VASE_2:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) - (camera[static_cast<int>(tNum)].GetCamera().y / scale.y),
							lpImage.GetID("image/map2.png")[static_cast<int>(id) - 8], true);
					}
					else
					{
						DrawGraph((x * ChipSize.x) - c_pos.x, (y * ChipSize.y) - c_pos.y, lpImage.GetID("image/map2.png")[static_cast<int>(id) - 8], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map2.png")[static_cast<int>(id) - 8], true);
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
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map3.png")[static_cast<int>(id) - 13], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map3.png")[static_cast<int>(id) - 13], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map3.png")[static_cast<int>(id) - 13], true);
				}
				break;
			case objID::BED:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map4.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map4.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map4.png")[0], true);
				}
				break;
			case objID::DESK:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map5.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map5.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 2) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map5.png")[0], true);
				}
				break;

			case objID::MONITOR:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map6.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map6.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 3) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 3) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map6.png")[0], true);
				}
				break;
			case objID::S_TABLE:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map7.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map7.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map7.png")[0], true);
				}
				break;
			case objID::TABLE:
				if (is_edit)
				{
					if (is_scale)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
							((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) - (c_pos.y / scale.y),
							lpImage.GetID("image/map8.png")[0], true);
					}
					else
					{
						DrawGraph((x * (ChipSize.x * scale.x)) - c_pos.x, (y * (ChipSize.y * scale.y)) - c_pos.y, lpImage.GetID("image/map8.png")[0], true);
					}
				}
				else
				{
					DrawExtendGraph((x * (ChipSize.x / scale.x)) - (c_pos.x / scale.x), (y * (ChipSize.y / scale.y)) - (c_pos.y / scale.y),
						((x * (ChipSize.x / scale.x)) + ((ChipSize.x * 2) / scale.x)) - (c_pos.x / scale.x), (((y * (ChipSize.y / scale.y))) + ((ChipSize.y * 4) / scale.y)) - (c_pos.y / scale.y),
						lpImage.GetID("image/map8.png")[0], true);
				}
				break;
				default:
					break;
			}
				if (!is_scale && !is_edit)
				{
					//if(objPos.x <= )
					DrawFormatString(((Scr.x / 2) * ((int)tNum - 1)) + (x * (ChipSize.x / blockScaleCnt.x) - c_pos.x), (y * (ChipSize.y / blockScaleCnt.y)) - c_pos.y, 0x000000, "x:%d\ny:%d\n%d", x, y, id);
				}
				if (is_edit)
				{
					DrawFormatString((Scr.x / 2) * ((int)tNum - 1) + (x * (ChipSize.x / mapScaleCnt.x) - c_pos.x), (y * (ChipSize.y / mapScaleCnt.y)) - c_pos.y, 0x000000, "x:%d\ny:%d\n%d", x, y, id);
				}
			
		}
	}
}

void Map::MapDraw(bool gameF)
{	
	// 画面分割(player人数毎に)
	switch (playerCnt)
	{
	case 1:
		
		// ｸﾞﾘｯﾄﾞの表示
		if (!is_scale)
		{
			for (int y = 0; y <= Scr.y; y += GRIDSIZE / blockScaleCnt.y)
			{
				DrawLine(0, y, Scr.x, y, 0xffffff);
				for (int x = 0; x <= Scr.x; x += GRIDSIZE / blockScaleCnt.x)
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
	case 2:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);
		// ｸﾞﾘｯﾄﾞの表示
		if (!is_scale)
		{
			for (int y = 0; y <= Scr.y; y += GRIDSIZE / blockScaleCnt.y)
			{
				DrawLine(0, y, Scr.x, y, 0xffffff);
				for (int x = 0; x <= Scr.x; x += GRIDSIZE / blockScaleCnt.x)
				{
					DrawLine(x, 0, x, Scr.y, 0xffffff);
				}
			}
		}

		// Mapの配置
		if (gameF)
		{
			DrawGraph(Scr.x / 2 - (MAPWINDOW_SIZE_X / 2), 0, MapWindow, false);
			DrawFormatString(Scr.x / 2 - 150, Scr.y - (Scr.y / 3) + 50, 0xffffff, "Map");
		}
		break;

	case 3:
		DrawLine(Scr.x / 2, 0, Scr.x / 2, Scr.y, 0xffffff);
		DrawLine(0, Scr.y / 2, Scr.x, Scr.y / 2, 0xffffff);
		// ｸﾞﾘｯﾄﾞの表示
		if (!is_scale)
		{
			for (int y = 0; y <= Scr.y; y += GRIDSIZE / blockScaleCnt.y)
			{
				DrawLine(0, y, Scr.x, y, 0xffffff);
				for (int x = 0; x <= Scr.x; x += GRIDSIZE / blockScaleCnt.x)
				{
					DrawLine(x, 0, x, Scr.y, 0xffffff);
				}
			}
		}
		
		// Mapの配置
		if (gameF)
		{
			DrawGraph((Scr.x - (Scr.x / 4)) - (MAPWINDOW_SIZE_X / 2), (Scr.y - (Scr.y / 4)) - (MAPWINDOW_SIZE_Y / 2), MapWindow, false);
			DrawFormatString(Scr.x / 2 + 150, Scr.y / 2 + (((Scr.y / 3) / 2) / 2) + 50, 0xffffff, "Map");
		}
		break;

	default:
		// ｸﾞﾘｯﾄﾞの表示
		if (!is_scale)
		{
			for (int y = 0; y <= Scr.y; y += GRIDSIZE / blockScaleCnt.y)
			{
				DrawLine(0, y, Scr.x, y, 0xffffff);
				for (int x = 0; x <= Scr.x; x += GRIDSIZE / blockScaleCnt.x)
				{
					DrawLine(x, 0, x, Scr.y, 0xffffff);
				}
			}
		}
		break;
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

//bool Map::_MakingPrey(WeakList weaklist)
//{
//	for (int y = 0; y < MapSize.y; y++)
//	{
//		for (int x = 0; x < MapSize.x; x++)
//		{
//			objID id = MapData[y][x];
//			switch (id)
//			{
//			case objID::PLAYER1:
//				if (!is_makePrey[typeNum1])
//				{
//					AddList()(weaklist, std::make_unique<Prey>(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), typeNum1, 1));
//					is_makePrey[typeNum1] = true;
//				}
//				break;
//			case objID::PLAYER2:
//				if (!is_makePrey[typeNum2])
//				{
//					AddList()(weaklist, std::make_unique<Prey>(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), typeNum2, 2));
//					is_makePrey[typeNum2] = true;
//				}
//				break;
//			case objID::PLAYER3:
//
//			case objID::WALL:
//			case objID::CHAIR_1:
//			case objID::CHAIR_2:
//			case objID::CHAIR_3:
//			case objID::CHAIR_4:
//
//			case objID::BOOKSHELF:
//			case objID::DRAWER:
//			case objID::LOCKER:
//			case objID::VASE_1:
//			case objID::VASE_2:
//
//			case objID::MIRRORTABLE:
//			case objID::FACE:
//			case objID::KITCHIN_1:
//			case objID::KITCHIN_2:
//			case objID::S_MONITOR:
//
//			case objID::BED:
//
//			case objID::DESK:
//
//			case objID::MONITOR:
//
//			case objID::S_TABLE:
//			case objID::TABLE:
//				break;
//			default:
//				break;
//			}
//		}
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

	mapScaleCnt = { 1,1 };
	blockScaleCnt = { 1,1 };

	is_scale = false;
	is_makePrey[PREY_3] = false;
	
	// すべてのﾏｯﾌﾟのｲﾝｽﾀﾝｽﾌﾗｸﾞをfalseにｾｯﾄ
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			makingPreyFlag[y][x] = false;
		}
	}

	is_mapCreate = false;

	is_preyWindowCreate = false;
	
	MapImage = LoadGraph("MAP/map_new.png");

	//----------------------------------
	return true;
}

void Map::CreateIndividualsDisplay(VECTOR2 ind_pos)
{
	// Mapの表示
	
	if (preyWindow >= 0 && !is_preyWindowCreate)
	{
		preyWindow = MakeScreen(MAPSIZE_X, MAPSIZE_Y);
		SetDrawScreen(preyWindow);
		DrawRectGraph(0,0,ind_pos.x, ind_pos.y,Scr.x / mapScaleCnt.x,Scr.y / mapScaleCnt.y, mapAllwindow, true, false);
		SetDrawScreen(DX_SCREEN_BACK);

		is_preyWindowCreate = true;
	}
}

void Map::CreateMap(void)
{
	// ﾏｯﾌﾟ全体の画像の生成
	if (mapAllwindow <= 0 && !is_mapCreate)
	{
		mapAllwindow = MakeScreen(MAPSIZE_X, MAPSIZE_Y, true);
		SetDrawScreen(mapAllwindow);
		DrawGraph(0, 0, MapImage, true);
		SetDrawScreen(DX_SCREEN_BACK);
		is_mapCreate = true;
	}	
}
			// Map画面表示
			//if (player == PLAYER_1 || player == PLAYER_2 || player == PLAYER_3)
			//{
			//	if (MapWindow >= 0)
			//	{
			//		MapWindow = MakeScreen(MAPWINDOW_SIZE_X, MAPWINDOW_SIZE_Y, true);
			//		SetDrawScreen(MapWindow);
			//		DrawBox(0, 0, MAPWINDOW_SIZE_X, MAPWINDOW_SIZE_Y, 0x0000ff, false);
			//		SetDrawScreen(DX_SCREEN_BACK);
			//	}
			//}
	

void Map::IndividualsDraw(bool gameF,PLAYER tNum,int pCnt,VECTOR2 c_pos)
{
	//DrawGraph(0, 0, mapAllwindow, true);
	// player1の画面表示
	
	if (pCnt == 1)
	{
		// ﾃﾞﾊﾞｯｸﾞ用-----------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		//---------------------------------------------
		DrawRectGraph(0, 0, c_pos.x, c_pos.y, Scr.x / mapScaleCnt.x, Scr.y / mapScaleCnt.y, mapAllwindow, true, false);
	}

	// player2の画面表示
	if (pCnt == 2)
	{
		DrawRectGraph((Scr.x / 2) * ((int)tNum - 1), 0, c_pos.x, c_pos.y, Scr.x / mapScaleCnt.x, Scr.y, mapAllwindow, true, false);
	}
	DrawCircle(0, 0, 5, 0x00ff00, true);
	// player3の画面表示
	if (pCnt == 3)
	{
		for (windowsNumX = 0; windowsNumX <= 1; windowsNumX++)
		{
			for (windowsNumY = 0; windowsNumY <= 1; windowsNumY++)
			{
				DrawRectExtendGraph((Scr.x / mapScaleCnt.x) * windowsNumX, (Scr.y / mapScaleCnt.y) * windowsNumY, (Scr.x / mapScaleCnt.x) * (windowsNumX + 1), (Scr.y / mapScaleCnt.y) * (windowsNumY + 1), camera[static_cast<int>(tNum)].GetCamera().x, camera[static_cast<int>(tNum)].GetCamera().y, Scr.x, Scr.y, mapAllwindow, true);
			}
		}
		// ﾃﾞﾊﾞｯｸﾞ用------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		DrawFormatString(50, Scr.y / 2 + 50, 0xffffff, "Player3");
			//----------------------------------------------------
	}
	if (!gameF)
	{
		DrawRectGraph(0, 0, c_pos.x, c_pos.y, Scr.x / mapScaleCnt.x, Scr.y / mapScaleCnt.y, mapAllwindow, true, false);
		if (is_scale)
		{
			DrawRectExtendGraph(0, 0, MAPSIZE_X / mapScaleCnt.x, MAPSIZE_Y / mapScaleCnt.y, c_pos.x, c_pos.y, MAPSIZE_X, MAPSIZE_Y, mapAllwindow, true);
		}
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

	//lpImage.GetID("image/Prey.png",VECTOR2(8,))
	// ----------------------------------------------------------------------------------
	ChangePreyMapScale();

	this->ChipSize = chipSize;

	MapSize = VECTOR2(size.x / (chipSize.x * blockScaleCnt.x),size.y / (chipSize.y * blockScaleCnt.y));

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

bool Map::setMapData(const VECTOR2 pos, objID id)
{
	return setData(MapData, pos, id);
}

// Map上のID情報を他に渡してあげる
objID Map::GetMapData(const VECTOR2 pos)
{
	return GetData(MapData, pos, objID::WALL);
}

// Map全体のｾｰﾌﾞ
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

// ｾｰﾌﾞしたMapのﾛｰﾄﾞ
bool Map::LoadMap(WeakList weaklist,bool loadF)
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
		SetObj(mapScaleCnt, false, weaklist);
	}
	else
	{
		SetObj(mapScaleCnt, true, weaklist);
	}
	return isCmp;
}

template<typename MapType, typename IDType>
bool Map::setData(MapType maptype, const VECTOR2 pos, IDType id)
{
	if (!is_scale)
	{
		VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x, pos.y / ChipSize.y);

		maptype[tmp.y][tmp.x] = id;
		_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", pos.x, pos.y, id);
	}
	return true;
}

template<typename MapType, typename IDType>
IDType Map::GetData(MapType maptype, const VECTOR2 pos, IDType defID)
{
	VECTOR2 tmp = VECTOR2(pos.x / (ChipSize.x / blockScaleCnt.x), pos.y / (ChipSize.y / blockScaleCnt.y));

	SetCheck setCheck;

	return maptype[tmp.y][tmp.x];
}


//VECTOR2 Map::IndividualsMapCalcPos(VECTOR2 pos,VECTOR2 camera,VECTOR2 indPos)
//{
//	indPos = pos - camera;
//	return indPos;
//}

bool Map::SetObj(VECTOR2 scale,bool is_edit,WeakList weaklist)
{
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			
			switch (id)
			{
			case objID::PLAYER1:
				if (is_edit)
				{
					break;
				}
				else
				{
					//if (instanceCnt >= 1)
					{
						camera.push_back(Camera(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), VECTOR2(240, 280), VECTOR2(GRIDSIZE, GRIDSIZE), PLAYER::PLAYER_1));

						AddList()(weaklist, std::make_unique<Prey>(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), typeNum1, PLAYER::PLAYER_1,camera[static_cast<int>(PLAYER::PLAYER_1)].GetCamera()));
						instanceCnt--;
					}
				}
				break;
			case objID::PLAYER2:
				if (is_edit)
				{
					break;
				}
				else
				{
					//if (instanceCnt >= 1)
					{
						camera.push_back(Camera(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), VECTOR2(240, 280), VECTOR2(GRIDSIZE, GRIDSIZE), PLAYER::PLAYER_2));

						AddList()(weaklist, std::make_unique<Prey>(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), typeNum2, PLAYER::PLAYER_2, camera[static_cast<int>(PLAYER::PLAYER_2)].GetCamera()));
						instanceCnt--;
					}
				}
					break;
			case objID::PLAYER3:
				if (is_edit)
				{
					break;
				}
				else
				{
					//if (instanceCnt >= 1)
					{
						camera.push_back(Camera(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), VECTOR2(240, 280), VECTOR2(GRIDSIZE, GRIDSIZE), PLAYER::PLAYER_3));

						AddList()(weaklist, std::make_unique<Prey>(VECTOR2(x * ChipSize.x, y * ChipSize.y - 40), typeNum3, PLAYER::PLAYER_3, camera[static_cast<int>(PLAYER::PLAYER_3)].GetCamera()));
						instanceCnt--;
					}
				}
				break;
			case objID::WALL:
			case objID::CHAIR_1:
			case objID::CHAIR_2:
			case objID::CHAIR_3:
			case objID::CHAIR_4:
			case objID::BOOKSHELF:
			case objID::DRAWER:
			case objID::LOCKER:
			case objID::VASE_1:
			case objID::VASE_2:
			case objID::MIRRORTABLE:
			case objID::FACE:
			case objID::KITCHIN_1:
			case objID::KITCHIN_2:
			case objID::S_MONITOR:
			case objID::BED:
			case objID::DESK:
			case objID::MONITOR:
			case objID::S_TABLE:
			case objID::TABLE:
			default:
				break;
			}
		}
	}
	return true;
}

bool Map::ChangeEditMapScale(Controller ctrl)
{
	auto cntNow = ctrl.GetKeyButtonInfo(KEY_TYPE_NOW);
	auto cntOld = ctrl.GetKeyButtonInfo(KEY_TYPE_OLD);
	
	if (cntNow[KEY_INPUT_COMMA] & ~cntOld[KEY_INPUT_COMMA]
		&& (mapScaleCnt.x == 1 && mapScaleCnt.y == 1))
	{

		mapScaleCnt.x *= 4;
		mapScaleCnt.y *= 4;
		is_scale = true;
	}
	if (cntNow[KEY_INPUT_PERIOD] & ~cntOld[KEY_INPUT_PERIOD]
		&& (mapScaleCnt.x == 4 && mapScaleCnt.y == 4))
	{
		mapScaleCnt.x /= 4;
		mapScaleCnt.y /= 4;
		is_scale = false;
	}
	return true;
}

bool Map::ChangePreyMapScale(void)
{
	switch (playerCnt)
	{
	case 1:

		blockScaleCnt.x = 1;
		blockScaleCnt.y = 1;
		mapScaleCnt.x = 1;
		mapScaleCnt.y = 1;
		break;
	case 2:

		blockScaleCnt.x = 1;
		blockScaleCnt.y = 1;
		mapScaleCnt.x = 2;
		mapScaleCnt.y = 1;
		break;
	case 3:

		blockScaleCnt.x = 2;
		blockScaleCnt.y = 2;
		mapScaleCnt.x = 2;
		mapScaleCnt.y = 2;
		break;
	default:
		break;
	}
	return true;
}

bool Map::ChangeInstanceCnt(void)
{
	switch (playerCnt)
	{
	case 1:
		instanceCnt = 1;
		break;

	case 2:
		instanceCnt = 2;
		break;

	case 3:
		instanceCnt = 3;
		break;

	default:
		break;
	}
	return true;
}

void Map::OtherPreyDraw(int ImageName,VECTOR2 indPos,int pCnt)
{
	
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			objID id = MapData[y][x];
			VECTOR2 eachOtherPos = VECTOR2((Scr.x / 2) * (pCnt - 1) + (x * ChipSize.x - indPos.x), (y * ChipSize.y - 40) - indPos.y);
			switch (id)
			{
			case objID::PLAYER1:
			case objID::PLAYER2:
			case objID::PLAYER3:
				//if (player == PLAYER_1 || player == PLAYER_2)
				{
					if ((pCnt == 1 && eachOtherPos.x <= Scr.x / 2) || (pCnt == 2 && eachOtherPos.x >= Scr.x / 2))
					{
						DrawGraph(eachOtherPos.x, eachOtherPos.y, ImageName, true);
					}
				}
				break;
			case objID::WALL:
			case objID::CHAIR_1:
			case objID::CHAIR_2:
			case objID::CHAIR_3:
			case objID::CHAIR_4:
			case objID::BOOKSHELF:
			case objID::DRAWER:
			case objID::LOCKER:
			case objID::VASE_1:
			case objID::VASE_2:
			case objID::MIRRORTABLE:
			case objID::FACE:
			case objID::KITCHIN_1:
			case objID::KITCHIN_2:
			case objID::S_MONITOR:
			case objID::BED:
			case objID::DESK:
			case objID::MONITOR:
			case objID::S_TABLE:
			case objID::TABLE:
				break;
			default:
				break;
			}
		}
	}
}

bool Map::objblock(VECTOR2 pos)
{

	pos = { pos.x, pos.y + 80 };
	bool block = true;
	objID id = GetMapData(pos);
	switch (id)
	{
	case objID::WALL:
	case objID::CHAIR_1:
	case objID::CHAIR_2:
	case objID::CHAIR_3:
	case objID::CHAIR_4:
		block = false;
		break;
	case objID::BOOKSHELF:
	case objID::DRAWER:
	case objID::LOCKER:
	case objID::VASE_1:
	case objID::VASE_2:
		block = false;
		break;
	case objID::MIRRORTABLE:
	case objID::FACE:
	case objID::KITCHIN_1:
	case objID::KITCHIN_2:
	case objID::S_MONITOR:
		block = false;
		break;
	case objID::BED:
		block = false;
		break;
	case objID::DESK:
		block = false;
		break;
	case objID::MONITOR:
		block = false;
		break;
	case objID::S_TABLE:
		block = false;
		break;
	case objID::TABLE:
		block = false;
		break;
	}
	return block;
}

Map::Map()
{
	Init();
}


Map::~Map()
{
}
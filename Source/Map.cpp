#include <DxLib.h>

#include "Map.h"
#include "Scene.h"
#include "Prey.h"
#include "Image.h"

struct DataHeader {
	char fileID[13];		//̧�ق�ID
	char VerID;				//�ް�ޮݔԍ�
	char reserve1[2];		//�\��̈�
	int	 SizeX;				//ϯ�߂�Ͻ�ڐ�X
	int  SizeY;				//ϯ�߂�Ͻ�ڐ�Y
	char reserve2[3];		//�\��̈�
	char sum;				//sum�l
};

#define SAVE_FILE_ID		"saveFile"
#define SAVE_FILE_VER_ID	0x01

void Map::Draw(void)
{
}

void Map::MapDraw(bool gameF)
{	
	// ��ʕ���(player�l������)
	switch (player)
	{
	case PLAYER_1:
		
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
		// ��د�ނ̕\��
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
	mapAllwindow = 0;
	preyWindow = 0;
	MapWindow = 0;

	cameraPos = { 320,320 };

	mapScaleCnt = { 1,1 };
	blockScaleCnt = { 1,1 };

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
	// Map�̕\��
	// ϯ�ߑS�̂̉摜�̐���
	if (mapAllwindow >= 0 && !is_mapCreate)
	{
		mapAllwindow = MakeScreen(MAPSIZE_X, MAPSIZE_Y, true);
		SetDrawScreen(mapAllwindow);
		DrawGraph(0,0, MapImage, true);
		SetDrawScreen(DX_SCREEN_BACK);

		is_mapCreate = true;
	}
	if (preyWindow >= 0 && !is_preyWindowCreate)
	{
		preyWindow = MakeScreen(MAPSIZE_X, MAPSIZE_Y);
		SetDrawScreen(preyWindow);
		DrawRectGraph(0,0, individualsMapPos.x, individualsMapPos.y,Scr.x / mapScaleCnt.x,Scr.y / mapScaleCnt.y, mapAllwindow, true, false);
		SetDrawScreen(DX_SCREEN_BACK);

		is_preyWindowCreate = true;
	}
}

void Map::IndividualsDraw(WeakList weaklist,bool gameF)
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
	//DrawGraph(0, 0, mapAllwindow, true);
	// player1�̉�ʕ\��
	if (player == PLAYER_1)
	{
		// ���ޯ�ޗp-----------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		//---------------------------------------------
		DrawRectGraph(0, 0, individualsMapPos.x, individualsMapPos.y, Scr.x / mapScaleCnt.x, Scr.y / mapScaleCnt.y, mapAllwindow, true, false);
		//DrawGraph(mapPos.x,mapPos.y, preyWindow, true);
		DrawFormatString(0, 100, 0xffffff, "ind_map.x:%d\nind_map.y;%d", individualsMapPos.x, individualsMapPos.y);

		//DrawGraph(mapPos.x, mapPos.y,preyWindow, true);
		// Prey�̲ݽ�ݽ(GameScene�̂�)
		if (gameF && !is_makePrey)
		{
			AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4 - 40),PREY_1));
			is_makePrey = true;
		}
	}

	// player2�̉�ʕ\��
	if (player == PLAYER_2)
	{
		for (windowsNumX = 0; windowsNumX <= 1; windowsNumX++)
		{
			DrawRectGraph((Scr.x / 2) * windowsNumX,0, individualsMapPos.x, individualsMapPos.y, Scr.x / mapScaleCnt.x, Scr.y, mapAllwindow, true,false);
		}
			// Prey�̲ݽ�ݽ(GameScene�̂�)
			if (gameF && !is_makePrey)
			{
				AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4 - 40), PREY_2));
				//AddList()(weaklist, std::make_unique<Prey>(VECTOR2((GRIDSIZE * 4) + (mapPos.x + (Scr.x * windowsNum)), (GRIDSIZE * 4 - 40) + (mapPos.y + (Scr.y * windowsNum))),PREY_2));

				is_makePrey = true;
			}
	}

	// player3�̉�ʕ\��
	if (player == PLAYER_3)
	{
		for (windowsNumX = 0; windowsNumX <= 1; windowsNumX++)
		{
			for (windowsNumY = 0; windowsNumY <= 1; windowsNumY++)
			{
				DrawRectExtendGraph((Scr.x / mapScaleCnt.x) * windowsNumX, (Scr.y / mapScaleCnt.y) * windowsNumY, (Scr.x / mapScaleCnt.x) * (windowsNumX + 1), (Scr.y / mapScaleCnt.y) * (windowsNumY + 1), individualsMapPos.x, individualsMapPos.y, Scr.x, Scr.y, mapAllwindow, true);
			}
		}
		// ���ޯ�ޗp------------------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		DrawFormatString(Scr.x / 2 + 50, 50, 0xffffff, "Player2");
		DrawFormatString(50, Scr.y / 2 + 50, 0xffffff, "Player3");
		//----------------------------------------------------
	}

	if (!gameF)
	{
		DrawExtendGraph(mapPos.x, mapPos.y, mapPos.x + (MAPSIZE_X / mapScaleCnt.x), mapPos.y + (MAPSIZE_Y / mapScaleCnt.y), MapImage, true);
	}
}

struct SetCheck
{
	bool operator()(const VECTOR2 &tmpPos, const VECTOR2 &MapSize) {
		//ϯ�ߓ��ł���΁A�`��OK
		if ((tmpPos.x < 1) || (tmpPos.y < 1) || ((MapSize.x / GRIDSIZE) <= tmpPos.x) || ((MapSize.y / GRIDSIZE) <= tmpPos.y))
		{
			return false;
		}
		return true;
	}
};

void Map::setUp(const VECTOR2& size, const VECTOR2& chipSize,PREY_NUM p_num)
{
	// ϯ�����߂̸��̨���̓ǂݍ���-------------------------------------------------------
	lpImage.GetID("image/map1.png", VECTOR2(3, 2), VECTOR2(GRIDSIZE,GRIDSIZE));
	lpImage.GetID("image/map2.png", VECTOR2(5, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 2));
	lpImage.GetID("image/map3.png", VECTOR2(5, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 3));
	lpImage.GetID("image/map4.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 2, GRIDSIZE * 3));
	lpImage.GetID("image/map5.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 3, GRIDSIZE * 2));
	lpImage.GetID("image/map6.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 3, GRIDSIZE * 3));
	lpImage.GetID("image/map7.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE, GRIDSIZE * 4));
	lpImage.GetID("image/map8.png", VECTOR2(1, 1), VECTOR2(GRIDSIZE * 2, GRIDSIZE * 4));
	// ----------------------------------------------------------------------------------
	ChangePreyMapScale();

	this->ChipSize = chipSize;

	MapSize = VECTOR2(size.x / (chipSize.x * blockScaleCnt.x),size.y / (chipSize.y * blockScaleCnt.y));

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
	createMap(BaseMap, MapData, objID::NON);
}

bool Map::setMapData(const VECTOR2 & pos, objID id)
{
	return setData(MapData,pos,id);
}

// Map���ID���𑼂ɓn���Ă�����
objID Map::GetMapData(const VECTOR2 & pos)
{
	return GetData(MapData,pos,objID::FLOOR);
}

bool Map::SaveMap(void)
{
	DataHeader expData = { SAVE_FILE_ID ,SAVE_FILE_VER_ID ,{ 0,0 },MapSize.x,MapSize.y ,{ 0,0,0 },0xff };

	// sum�l
	int sumValue = 0;
	//sum�l�̌v�Z
	for (auto data : BaseMap)
	{
		sumValue += (int)data;
	}

	expData.sum = (char)sumValue;

	FILE *file;
	fopen_s(&file, "MapData/SaveData.map", "wb");				//�J��
	fwrite(&expData, sizeof(expData), 1, file);				//��������
															//��map�����ۯ����ǂ��ɔz�u���������ް�
	fwrite(BaseMap.data(), sizeof(objID) * BaseMap.size(), 1, file);		//map_b_data.data()�������߲��	fwrite(�������݂����ް��������Ă���擪�߲��,�n���ް����޲Đ�,�ŏ��P�ʂ��ް��̉�����񏑂����ނ�,�������ނׂ�̧�ق��߲��)
																				//map_b_data.size()�ŏ�����������Ες��Ȃ��l�Ȃ̂ŁA���S�B
																				//�ǂ���ł��L�qOK
																				//fwrite(&map_b_data[0], sizeof(map_b_data[0]), 1, file);
	fclose(file);											//����
	return false;
}

bool Map::LoadMap(void)
{
	FILE* file;
	DataHeader expData;
	fopen_s(&file, "MapData/SaveData.map", "rb");		//	�J��
	fread(&expData, sizeof(expData), 1, file);		//	�ǂݍ���
													//ͯ�ް�̻��ޏ�������map_b_data�̻��ނ�ػ��ނ���B//map_b_data��ǂݍ��ނ܂łɈ�ԍő����Œx�B
	BaseMap.resize(expData.SizeX * expData.SizeY);
	fread(BaseMap.data(), sizeof(objID) * BaseMap.size(), 1, file);//	�ǂݍ���
	fclose(file);	//	����

	// isCmp : ��r�����׸�
	bool isCmp = true;
	if ((std::string)expData.fileID != SAVE_FILE_ID)
	{
		isCmp = false;
	}
	//ͯ�ް���ް�ޮݔԍ��Ɠ����Ŏ����Ă���ԍ����ׂ�B
	if (expData.VerID != SAVE_FILE_VER_ID)
	{
		isCmp = false;
	}
	//sum�l��ͯ�ް�̒l���ׂĈ������A�ް���ر����B
	int SumValue = 0;

	//�擾�����l��Sum�ɓ���Ă����A�ǂ�ǂ���Z���Ă����B
	for (auto data : BaseMap)
	{
		SumValue += (int)data;
	}

	//Sum�̒l�ƌ��̒l���Ⴄ�̂ł���΁Afalse�ɁB
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
		//auto�Q�Ƃɂ��邱�Ƃ�map_b_data�S�̂����Ă�Ƃ������ƂɂȂ�
		//�l�n���ɂ����map_b_data�����邱�Ƃɂ͂Ȃ�Ȃ��B
		for (auto &data : BaseMap)
		{
			data = objID::NON;
		}
	}
	//isCmp == true ���@������load���ꂽ�Ƃ�
	if (isCmp)
	{
		SetObj(blockScaleCnt,false);
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

		// ����Ă������߂��߼޼�ݏ������̂܂ܑS�̂�ϯ�߂Ɋi�[
		// ϯ�߂̈ړ��Ƌ������߂��������Ȃ��Ƃ����Ȃ��̂�
		//setPos = tmp;
		// Map���łȂ��ꍇ�͕`�悵�Ȃ�
		/*if (!SetCheck()(tmp, MapSize));
		{
			return false;
		}*/
		// Map���̏ꍇ�͕`��OK
		//maptype[setPos.y][setPos.x] = maptype[tmp.y][tmp.x];

		maptype[tmp.y][tmp.x] = id;
	}
	_RPTN(_CRT_WARN, "ID:[%d:%d]%d\n", pos.x, pos.y, id);
	return true;
}

template<typename MapType, typename IDType>
IDType Map::GetData(MapType maptype, const VECTOR2 & pos, IDType defID)
{
	VECTOR2 tmp = VECTOR2(pos.x / (ChipSize.x / blockScaleCnt.x), pos.y / (ChipSize.y / blockScaleCnt.y));

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
					if (player == PLAYER_1)
					{
						DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x, (y * (ChipSize.y / scale.y)) + mapPos.y,
							((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x, (((y * (ChipSize.y / scale.y))) + (ChipSize.y / scale.y)) + mapPos.y,
							lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
					}
					else if (player == PLAYER_2)
					{
						for (windowsNumX = 0; windowsNumX < 2; windowsNumX++)
						{
							DrawExtendGraph((x * (ChipSize.x / scale.x)) + mapPos.x + ((Scr.x / 2) * windowsNumX), (y * (ChipSize.y / scale.y)) + mapPos.y + ((Scr.y / 2) * windowsNumX),
								((x * (ChipSize.x / scale.x)) + (ChipSize.x / scale.x)) + mapPos.x + ((Scr.x / 2) * windowsNumX), (((y * (ChipSize.y / scale.y))) + (ChipSize.y / scale.y)) + mapPos.y + ((Scr.y / 2) * windowsNumX),
								lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
						}
					}
					else if(player == PLAYER_3)
					{

					}
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
				DrawFormatString((x * (ChipSize.x / blockScaleCnt.x)) + mapPos.x, (y * (ChipSize.y / blockScaleCnt.y)) + mapPos.y, 0xff0000, "x:%d\ny:%d\n%d", x, y, id);
			}
		}
	}

	return true;
}

bool Map::ChangeEditMapScale(Controller ctrl)
{
	auto cntNow = ctrl.GetButtonInfo(KEY_TYPE_NOW);
	auto cntOld = ctrl.GetButtonInfo(KEY_TYPE_OLD);
	
	if (cntNow[KEY_INPUT_COMMA] & ~cntOld[KEY_INPUT_COMMA]
		&& (mapScaleCnt.x == 1 && mapScaleCnt.y == 1))
	{
		mapPos = { 0,0 };

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
	switch (player)
	{
	case PLAYER_1:
		blockScaleCnt.x = 1;
		blockScaleCnt.y = 1;
		mapScaleCnt.x = 1;
		mapScaleCnt.y = 1;
		break;
	case PLAYER_2:
		blockScaleCnt.x = 1;
		blockScaleCnt.y = 1;
		mapScaleCnt.x = 2;
		mapScaleCnt.y = 2;
		break;
	case PLAYER_3:
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

Map::Map()
{
	Init();

	is_makePrey = false;
}


Map::~Map()
{
}
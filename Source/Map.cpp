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
	MapImage = LoadGraph("MAP/map_new.png");

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

	// player1�̉�ʕ\��
	if (player == PLAYER_1)
	{

		// ���ޯ�ޗp-----------------------------------
		DrawFormatString(50, 50, 0xffffff, "Player1");
		//---------------------------------------------

		DrawGraph(0, 0, PreyWindow, true);

		// Map�̕\��
		DrawRectGraph(mapPos.x, mapPos.y,0,0,MAPSIZE_X,MAPSIZE_Y, MapImage, true,false);

		// Prey(��)�̕\��
		//DrawBox(GRIDSIZE * 4,(GRIDSIZE * 4) - 40,(GRIDSIZE * 4) + PREYSIZE_X,(GRIDSIZE * 5), 0xff0000, true);
		// Prey�̲ݽ�ݽ(GameScene�̂�)
		if (gameF && !is_makePrey)
		{
			AddList()(weaklist, std::make_unique<Prey>(VECTOR2(GRIDSIZE * 4, GRIDSIZE * 4 - 40)));
			is_makePrey = true;
		}
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

void Map::setUp(const VECTOR2& size, const VECTOR2& chipSize)
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
		SetObj();
	}

	return isCmp;
}

template<typename MapType, typename IDType>
bool Map::setData(MapType maptype, const VECTOR2 & pos, IDType id)
{
	//ChangeChipSize();
	VECTOR2 tmp = VECTOR2(pos.x / ChipSize.x ,pos.y / ChipSize.y);
	


	// ����Ă������߂��߼޼�ݏ������̂܂ܑS�̂�ϯ�߂Ɋi�[
	// ϯ�߂̈ړ��Ƌ������߂��������Ȃ��Ƃ����Ȃ��̂�


	// Map���łȂ��ꍇ�͕`�悵�Ȃ�
	/*if (!SetCheck()(tmp, MapSize));
	{
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

	SetCheck setCheck;

	if (!setCheck(tmp,MapSize))
	{
		return defID;
	}
	return maptype[tmp.y][tmp.x];
}

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
				DrawGraph(x * ChipSize.x,y * ChipSize.y, lpImage.GetID("image/map1.png")[static_cast<int>(id)], true);
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

	is_makePrey = false;
}


Map::~Map()
{
}
#pragma once
#include <vector>
#include "VECTOR2.h"
#include "AddList.h"
#include "objID.h"
#include "Obj.h"


#define lpMap Map::getIns()

// 1Ͻ�̻���
#define GRIDSIZE 80

// Ͻ��(��)
#define GRIDCNT_X	15
// Ͻ��(�c)
#define GRIDCNT_Y	8

// Map����޳�̻���
#define MAPWINDOW_SIZE_X GRIDSIZE * 6
#define MAPWINDOW_SIZE_Y 214

// player�̐悪�ǂ�����
enum PASSAGE
{
	PASSAGE_WAY,	// ��
	PASSAGE_WALL	// ��
};


// �����鑤�̐l��
enum PLAYER
{
	PLAYER_1,		// 1�l
	PLAYER_2,		// 2�l
	PLAYER_3,		// 3�l
	PLAYER_MAX
};

class Map
{
public:
	static Map &getIns(void)
	{
		static Map mapins;
		return mapins;
	}
	// Map�̵�޼ު�Ă̕`��
	void Draw(void);

	// Map��Grid�̕\��(Ͻ�m�F�p) gameF:�ްѼ�݂Ɉڍs���Ă��邩�ǂ��� true:GameScene false:EditScene
	void MapDraw(bool gameF);

	// ϯ�߂̑S�̂��Ƃ肠����WALL(��)�ŏ�����
	bool MapInit(void)
	{
		for (int y = 0; y <= GRIDCNT_Y; y++)
		{
			for (int x = 0; x <= GRIDCNT_X; x++)
			{
				passageF[(y * x) + x] = PASSAGE_WALL;
			}
		}
		return true;
	}

	//bool CheckPassage(VECTOR2 pos, PASSAGE passage,DIR dir);

	// �e�ϐ��̏������֐�
	bool Init(void);

	// �e��ڲ԰���ި���ڲ�����֐�
	void CreateIndividualsDisplay(void);

	// �e��ڲ԰���ި���ڲ�̕`��֐�
	void IndividualsDraw(WeakList weaklist);

	void setUp(const VECTOR2& size, const VECTOR2& chipSize);

	bool setMapData(const VECTOR2& pos, objID id);
	objID GetMapData(const VECTOR2& pos);

	// ��ڲ԰�̐l���̊i�[�ϐ�
	PLAYER player;
private:
	Map();
	~Map();

	// ϯ�߂̍�����߼޼��
	VECTOR2 mapPos;

	// ϯ�߂̉摜
	int MapImage;

	// �e����޳(�ǐՂ���鑤)
	int PreyWindow;

	// ϯ�ߐ�p�̳���޳
	int MapWindow;

	// ��ذݑS�̻̂���
	VECTOR2 Scr;

	// ϯ�߂�1Ͻ1Ͻ���ް�
	std::vector<objID*>MapData;
	// ϯ�߂̑S�̂��ް�
	std::vector<objID>BaseMap;
	

	// 
	VECTOR2 MapSize;
	// 1���߂̻���
	VECTOR2 ChipSize;
	
	// �����ǂ����׸�
	PASSAGE passageF[GRIDCNT_X * GRIDCNT_Y];

	//	�����̂Ƃ���Œu���������^�Ő錾����Ƃ�������
	template<typename MapType, typename IDType>
	// Map�����ߏ��𖄂ߍ��ފ֐�
	bool setData(MapType maptype, const VECTOR2& pos, IDType id);

	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2& pos, IDType defID);
};



#pragma once
#include <vector>

#include "Obj.h"

#include "NUM_TYPE.h"
#include "Controller.h"
#include "VECTOR2.h"
#include "AddList.h"
#include "objID.h"
//#include "Prey.h"



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

// Map�̸��̨���̻���
#define MAPSIZE_X	12000
#define MAPSIZE_Y	8640


// player�̐悪�ǂ�����
enum PASSAGE
{
	PASSAGE_WAY,	// ��
	PASSAGE_WALL,	// ��
	PASSAGE_MAX
};


// �l���ɉ�����mode��ύX
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
	void CreateIndividualsDisplay(VECTOR2 ind_pos);

	void CreateMap(void);

	// �e��ڲ԰���ި���ڲ�̕`��֐�
	void IndividualsDraw(bool gameF,VECTOR2 ind_pos,int num);

	// ��ʂ̾��
	void setUp(const VECTOR2& size, const VECTOR2& chipSize);

	bool setMapData(const VECTOR2 pos, objID id);
	objID GetMapData(const VECTOR2 pos);

	void _PreyInstance(WeakList weaklist,VECTOR2 pos,bool is_edit,int num);
	void _ItInstance(WeakList weaklist, VECTOR2 pos, bool is_edit, int num);

	//	�ް����ފ֐�
	bool SaveMap(void);
	//	�ް�۰�ފ֐�
	bool LoadMap(VECTOR2 indPos,int num);

	
	// Map�̻��ގ擾
	VECTOR2 GetMapSize(void)
	{
		return VECTOR2(MAPSIZE_X, MAPSIZE_Y);
	}
	// ��Ͻ�̻��ނ̎擾
	VECTOR2 GetGridSize(void)
	{
		return VECTOR2(GRIDSIZE, GRIDSIZE);
	}
	// �g��k�����������׸ނ̎擾
	bool Get_isScale(void)
	{
		return is_scale;
	}


	// �ʂ�ϯ�߳���޳���߼޼�݌v�Z�֐�
	VECTOR2 IndividualsMapCalcPos(VECTOR2 pos,VECTOR2 camera,VECTOR2 ind_pos);

	// ��Ă�����޼ު�Ă̕`��
	bool SetObj(VECTOR2 scale,bool is_edit,VECTOR2 indPos,int num);

	// Map�̊g��k��(EditScene�̂�)
	bool ChangeEditMapScale(Controller ctrl,VECTOR2 indPos);
	// Map�̊g��k�����̌���֐�(GameScene�̂�)
	bool ChangePreyMapScale(void);

	// ��ڲ�l���ɂ������ڲ԰�̲ݽ�ݽ���𐧌�
	bool ChangeInstanceCnt(void);
	// Map�̊g��k����
	VECTOR2 mapScaleCnt;
	// ���ꂼ������߂̊g��k����
	VECTOR2 blockScaleCnt;

	// ��ڲ԰�̐l���̊i�[�ϐ�
	PLAYER player;
	
private:
	Map();
	~Map();

	VECTOR2 setPos;

	// ���ق��߼޼�ݕ␳�̂��߂̶���߼޼��
	//VECTOR2 cameraPos[PREY_MAX];

	// Map���g��k�����Ă��邩�ǂ������׸�
	bool is_scale;

	// ϯ�߂̉摜
	int MapImage;

	// �S�̂�ϯ�߉摜
	int mapAllwindow;

	int preyWindow;
	
	// �e����޳�A�S��ϯ�߂̕`�搧���׸�
	bool is_mapCreate;

	bool is_mapSet;

	bool is_preyWindowCreate;

	// ϯ�ߐ�p�̳���޳
	int MapWindow;

	// �Q�[����ʂ𕪊������ۂ̕�����X��
	int windowsNumX;
	// �Q�[����ʂ𕪊������ۂ̕�����Y��
	int windowsNumY;

	// ��ذݑS�̻̂���
	VECTOR2 Scr;
	// ��ڲ԰�ݽ�ݽ�׸�(�J��Ԃ��ݽ�ݽ�̖h�~)
	bool is_makePrey[PREY_3];

	// ��ڲ԰�̲ݽ�ݽ���̐�������
	int instanceCnt;


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
	bool setData(MapType maptype, const VECTOR2 pos, IDType id);

	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2 pos, IDType defID);
};



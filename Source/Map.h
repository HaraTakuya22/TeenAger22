#pragma once
#include "VECTOR2.h"
#include "AddList.h"


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

	// Map��Grid�̕\��(Ͻ�m�F�p)
	void MapDraw(void);

	// ϯ�߂̑S�̂��Ƃ肠����WALL(��)�ŏ�����
	bool MapInit(void)
	{
		
		return true;
	}

	// �e�ϐ��̏������֐�
	bool Init(void);

	// �e��ڲ԰���ި���ڲ�����֐�
	void CreateIndividualsDisplay(void);

	// �e��ڲ԰���ި���ڲ�̕`��֐�
	void IndividualsDraw(WeakList weaklist);

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
};


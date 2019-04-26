#pragma once
#include "VECTOR2.h"
#include "AddList.h"


#define lpMap Map::getIns()

// 1ﾏｽのｻｲｽﾞ
#define GRIDSIZE 80

// ﾏｽ目(横)
#define GRIDCNT_X	15
// ﾏｽ目(縦)
#define GRIDCNT_Y	8


// Mapｳｨﾝﾄﾞｳのｻｲｽﾞ
#define MAPWINDOW_SIZE_X GRIDSIZE * 6
#define MAPWINDOW_SIZE_Y 214

// playerの先が壁か道か
enum PASSAGE
{
	PASSAGE_WAY,	// 道
	PASSAGE_WALL	// 壁
};


// 逃げる側の人数
enum PLAYER
{
	PLAYER_1,		// 1人
	PLAYER_2,		// 2人
	PLAYER_3,		// 3人
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
	// Mapのｵﾌﾞｼﾞｪｸﾄの描画
	void Draw(void);

	// MapのGridの表示(ﾏｽ確認用)
	void MapDraw(void);

	// ﾏｯﾌﾟの全体をとりあえずWALL(壁)で初期化
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

	// 各変数の初期化関数
	bool Init(void);

	// 各ﾌﾟﾚｲﾔｰのﾃﾞｨｽﾌﾟﾚｲ生成関数
	void CreateIndividualsDisplay(void);

	// 各ﾌﾟﾚｲﾔｰのﾃﾞｨｽﾌﾟﾚｲの描画関数
	void IndividualsDraw(WeakList weaklist);

	// ﾌﾟﾚｲﾔｰの人数の格納変数
	PLAYER player;
private:
	Map();
	~Map();

	// ﾏｯﾌﾟの左上のﾎﾟｼﾞｼｮﾝ
	VECTOR2 mapPos;

	// ﾏｯﾌﾟの画像
	int MapImage;

	// 各ｳｨﾝﾄﾞｳ(追跡される側)
	int PreyWindow;

	// ﾏｯﾌﾟ専用のｳｨﾝﾄﾞｳ
	int MapWindow;

	// ｽｸﾘｰﾝ全体のｻｲｽﾞ
	VECTOR2 Scr;
	
	// 道か壁かのﾌﾗｸﾞ
	PASSAGE passageF[GRIDCNT_X * GRIDCNT_Y];
};


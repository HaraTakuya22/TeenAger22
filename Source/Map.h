#pragma once
#include <vector>
#include "Controller.h"
#include "VECTOR2.h"
#include "AddList.h"
#include "objID.h"
#include "Obj.h"


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

// Mapのｸﾞﾗﾌｨｯｸのｻｲｽﾞ
#define MAPSIZE_X	12000
#define MAPSIZE_Y	8640


// playerの先が壁か道か
enum PASSAGE
{
	PASSAGE_WAY,	// 道
	PASSAGE_WALL,	// 壁
	PASSAGE_MAX
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

	// MapのGridの表示(ﾏｽ確認用) gameF:ｹﾞｰﾑｼｰﾝに移行しているかどうか true:GameScene false:EditScene
	void MapDraw(bool gameF);

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
	void IndividualsDraw(WeakList weaklist,bool gameF);

	// 画面のｾｯﾄ
	void setUp(const VECTOR2& size, const VECTOR2& chipSize);

	bool setMapData(const VECTOR2& pos, objID id);
	objID GetMapData(const VECTOR2& pos);

	//	ﾃﾞｰﾀｾｰﾌﾞ関数
	bool SaveMap(void);
	//	ﾃﾞｰﾀﾛｰﾄﾞ関数
	bool LoadMap(void);

	// ﾏｯﾌﾟのﾎﾟｼﾞｼｮﾝ取得
	VECTOR2& GetMapPos(void)
	{
		return mapPos;
	}
	// Mapのｻｲｽﾞ取得
	VECTOR2 GetMapSize(void)
	{
		return VECTOR2(MAPSIZE_X, MAPSIZE_Y);
	}
	// 一ﾏｽのｻｲｽﾞの取得
	VECTOR2 GetGridSize(void)
	{
		return VECTOR2(GRIDSIZE, GRIDSIZE);
	}
	// 拡大縮小したかのﾌﾗｸﾞの取得
	bool Get_isScale(void)
	{
		return is_scale;
	}

	// cameraのﾎﾟｼﾞｼｮﾝの取得
	VECTOR2 GetCamera(void)
	{
		return cameraPos;
	}

	VECTOR2 MapCalcPos(VECTOR2 c_pos,VECTOR2 scroll);
	// ｾｯﾄしたｵﾌﾞｼﾞｪｸﾄの描画
	bool SetObj(VECTOR2 scale);

	// Mapの拡大縮小(EditSceneのみ)
	bool ChangeMapScale(bool editF,Controller ctrl);
	// Map全体の拡大縮小率
	VECTOR2 scaleCnt;
	VECTOR2 gameWindowScale;

	// ﾌﾟﾚｲﾔｰの人数の格納変数
	PLAYER player;

private:
	Map();
	~Map();

	VECTOR2 setPos;

	// ﾏｯﾌﾟの左上のﾎﾟｼﾞｼｮﾝ
	VECTOR2 mapPos;
	// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ補正のためのｶﾒﾗﾎﾟｼﾞｼｮﾝ
	VECTOR2 cameraPos;

	// Mapを拡大縮小しているかどうかのﾌﾗｸﾞ
	bool is_scale;

	// ﾏｯﾌﾟの画像
	int MapImage;

	// 各ｳｨﾝﾄﾞｳ(追跡される側)
	int Preywindow;

	// ﾏｯﾌﾟ専用のｳｨﾝﾄﾞｳ
	int MapWindow;

	// ｽｸﾘｰﾝ全体のｻｲｽﾞ
	VECTOR2 Scr;



	// ﾏｯﾌﾟの1ﾏｽ1ﾏｽのﾃﾞｰﾀ
	std::vector<objID*>MapData;
	// ﾏｯﾌﾟの全体のﾃﾞｰﾀ
	std::vector<objID>BaseMap;
	

	// 
	VECTOR2 MapSize;
	// 1ﾁｯﾌﾟのｻｲｽﾞ
	VECTOR2 ChipSize;
	
	// 道か壁かのﾌﾗｸﾞ
	PASSAGE passageF[GRIDCNT_X * GRIDCNT_Y];


	// ﾌﾟﾚｲﾔｰｲﾝｽﾀﾝｽﾌﾗｸﾞ(繰り返しｲﾝｽﾀﾝｽの防止)
	bool is_makePrey;
	

	//	引数のところで置き換えた型で宣言するということ
	template<typename MapType, typename IDType>
	// Mapにﾁｯﾌﾟ情報を埋め込む関数
	bool setData(MapType maptype, const VECTOR2& pos, IDType id);

	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2& pos, IDType defID);
};



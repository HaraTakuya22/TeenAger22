#pragma once
#include <vector>

#include "Obj.h"

#include "Controller.h"
#include "VECTOR2.h"
#include "AddList.h"
#include "objID.h"
//#include "Prey.h"



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


// 人数に応じてmodeを変更
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

	bool setMapData(const VECTOR2* pos, objID id);
	objID GetMapData(const VECTOR2* pos);

	//	ﾃﾞｰﾀｾｰﾌﾞ関数
	bool SaveMap(void);
	//	ﾃﾞｰﾀﾛｰﾄﾞ関数
	bool LoadMap(void);

	// ﾏｯﾌﾟのﾎﾟｼﾞｼｮﾝ取得
	VECTOR2& GetMapPos(void)
	{
		return mapPos[typeNum];
	}
	VECTOR2& GetIndividualsmapPos(void)
	{
		return individualsMapPos[typeNum];
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

	// ｶｰｿﾙのcameraﾎﾟｼﾞｼｮﾝの取得
	VECTOR2 GetCamera(void)
	{
		return cameraPos;
	}

	// ﾏｯﾌﾟのﾎﾟｼﾞｼｮﾝ計算関数
	VECTOR2 MapCalcPos(VECTOR2* c_pos,VECTOR2 scroll);

	// 個別のﾏｯﾌﾟｳｨﾝﾄﾞｳのﾎﾟｼﾞｼｮﾝ計算関数
	VECTOR2& IndividualsMapCalcPos(VECTOR2* pos,VECTOR2 camera);

	

	// ｾｯﾄしたｵﾌﾞｼﾞｪｸﾄの描画
	bool SetObj(VECTOR2 scale,bool is_edit);

	// Mapの拡大縮小(EditSceneのみ)
	bool ChangeEditMapScale(Controller ctrl);
	// Mapの拡大縮小率の決定関数(GameSceneのみ)
	bool ChangePreyMapScale(void);
	// Mapの拡大縮小率
	VECTOR2 mapScaleCnt;
	// それぞれのﾁｯﾌﾟの拡大縮小率
	VECTOR2 blockScaleCnt;

	// ﾌﾟﾚｲﾔｰの人数の格納変数
	PLAYER player;
	TYPE_NUM typeNum;
private:
	Map();
	~Map();

	VECTOR2 setPos;

	// ﾏｯﾌﾟの左上のﾎﾟｼﾞｼｮﾝ
	VECTOR2 mapPos[PREY_MAX];

	// ﾌﾟﾚｲﾔｰ毎のﾏｯﾌﾟ画面のﾎﾟｼﾞｼｮﾝ
	VECTOR2 individualsMapPos[PREY_MAX];

	// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ補正のためのｶﾒﾗﾎﾟｼﾞｼｮﾝ
	VECTOR2 cameraPos;
	// Mapを拡大縮小しているかどうかのﾌﾗｸﾞ
	bool is_scale;

	// ﾏｯﾌﾟの画像
	int MapImage;

	// 全体のﾏｯﾌﾟ画像
	int mapAllwindow;

	int preyWindow;
	
	// 各ｳｨﾝﾄﾞｳ、全体ﾏｯﾌﾟの描画制御ﾌﾗｸﾞ
	bool is_mapCreate;
	bool is_preyWindowCreate;

	// ﾏｯﾌﾟ専用のｳｨﾝﾄﾞｳ
	int MapWindow;

	// ゲーム画面を分割した際の分割回数X軸
	int windowsNumX;
	// ゲーム画面を分割した際の分割回数Y軸
	int windowsNumY;

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
	bool setData(MapType maptype, const VECTOR2* pos, IDType id);

	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2& pos, IDType defID);
};



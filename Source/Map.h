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
	PLAYER_IT,
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
	void Draw(bool is_edit, VECTOR2 scale, VECTOR2 indPos, int pCnt);

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
	//bool _MakingPrey(WeakList weaklist);

	// 各変数の初期化関数
	bool Init(void);

	// 各ﾌﾟﾚｲﾔｰのﾃﾞｨｽﾌﾟﾚｲ生成関数
	void CreateIndividualsDisplay(VECTOR2 ind_pos);

	void CreateMap(void);

	// 各ﾌﾟﾚｲﾔｰのﾃﾞｨｽﾌﾟﾚｲの描画関数
	void IndividualsDraw(bool gameF,VECTOR2 indPos,int pCnt);

	// 画面のｾｯﾄ
	void setUp(const VECTOR2& size, const VECTOR2& chipSize);

	bool setMapData(const VECTOR2 pos, objID id);
	objID GetMapData(const VECTOR2 pos);



	//	ﾃﾞｰﾀｾｰﾌﾞ関数
	bool SaveMap(void);
	//	ﾃﾞｰﾀﾛｰﾄﾞ関数
	bool LoadMap(WeakList weaklist,bool loadF);

	
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


	// 個別のﾏｯﾌﾟｳｨﾝﾄﾞｳのﾎﾟｼﾞｼｮﾝ計算関数
	VECTOR2 IndividualsMapCalcPos(VECTOR2 pos,VECTOR2 camera,VECTOR2 indPos);

	// ｾｯﾄしたｵﾌﾞｼﾞｪｸﾄの描画(num:1P 2P or 3P is_edit:ｴﾃﾞｨｯﾄﾓｰﾄﾞかどうかのﾌﾗｸﾞ scale:ﾏｯﾌﾟの拡大縮小率)
	bool SetObj(VECTOR2 scale,bool is_edit,WeakList weaklist);

	// Mapの拡大縮小(EditSceneのみ)
	bool ChangeEditMapScale(Controller ctrl,VECTOR2 indPos);
	// Mapの拡大縮小率の決定関数(GameSceneのみ)
	bool ChangePreyMapScale(void);

	// ﾌﾟﾚｲ人数によってﾌﾟﾚｲﾔｰのｲﾝｽﾀﾝｽ数を制限
	bool ChangeInstanceCnt(void);
	// Mapの拡大縮小率
	VECTOR2 mapScaleCnt;
	// それぞれのﾁｯﾌﾟの拡大縮小率
	VECTOR2 blockScaleCnt;

	// ﾌﾟﾚｲﾔｰの人数の格納変数
	PLAYER player;

	bool objblock(VECTOR2 pos);
	
private:
	Map();
	~Map();


	// ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ補正のためのｶﾒﾗﾎﾟｼﾞｼｮﾝ
	//VECTOR2 cameraPos[PREY_MAX];

	// Mapを拡大縮小しているかどうかのﾌﾗｸﾞ
	bool is_scale;

	// ﾏｯﾌﾟの画像
	int MapImage;

	// 全体のﾏｯﾌﾟ画像
	int mapAllwindow;

	// ※廃止予定
	int preyWindow;
	
	// 各ｳｨﾝﾄﾞｳ、全体ﾏｯﾌﾟの描画制御ﾌﾗｸﾞ
	bool is_mapCreate;

	// ※廃止予定
	bool is_preyWindowCreate;

	// ﾏｯﾌﾟ専用のｳｨﾝﾄﾞｳ
	int MapWindow;

	// ゲーム画面を分割した際の分割回数X軸
	int windowsNumX;
	// ゲーム画面を分割した際の分割回数Y軸
	int windowsNumY;

	// ｽｸﾘｰﾝ全体のｻｲｽﾞ
	VECTOR2 Scr;
	// ﾌﾟﾚｲﾔｰｲﾝｽﾀﾝｽﾌﾗｸﾞ(繰り返しｲﾝｽﾀﾝｽの防止)
	bool is_makePrey[PREY_3];

	// ﾌﾟﾚｲﾔｰのｲﾝｽﾀﾝｽ数の制限ｶｳﾝﾄ
	int instanceCnt;


	// ﾏｯﾌﾟの1ﾏｽ1ﾏｽのﾃﾞｰﾀ
	std::vector<objID*>MapData;
	// ﾏｯﾌﾟの全体のﾃﾞｰﾀ
	std::vector<objID>BaseMap;
	

	// ﾏｯﾌﾟをﾁｯﾌﾟ単位で表したｻｲｽﾞ
	VECTOR2 MapSize;
	// 1ﾁｯﾌﾟのｻｲｽﾞ
	VECTOR2 ChipSize;
	
	// 道か壁かのﾌﾗｸﾞ
	PASSAGE passageF[GRIDCNT_X * GRIDCNT_Y];

	// ﾏｯﾌﾟ単位のpreyのｲﾝｽﾀﾝｽﾌﾗｸﾞ
	// 同じところにはｲﾝｽﾀﾝｽしたくないため

	bool makingPreyFlag[MAPSIZE_X / GRIDSIZE][MAPSIZE_Y / GRIDSIZE];
	
	

	//	引数のところで置き換えた型で宣言するということ
	template<typename MapType, typename IDType>
	// Mapにﾁｯﾌﾟ情報を埋め込む関数
	bool setData(MapType maptype, const VECTOR2 pos, IDType id);

	// ﾏｯﾌﾟの情報を取得
	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2 pos, IDType defID);
};



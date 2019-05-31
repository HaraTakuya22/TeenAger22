#pragma once
#include <vector>
#include <string>

#include "Obj.h"
#include "PLAYER.h"
#include "NUM_TYPE.h"
#include "Controller.h"
#include "VECTOR2.h"
#include "AddList.h"
#include "objID.h"



#define lpMap Map::getIns()

// 1Ï½‚Ì»²½Ş
#define GRIDSIZE 80

// Ï½–Ú(‰¡)
#define GRIDCNT_X	15
// Ï½–Ú(c)
#define GRIDCNT_Y	8

// Map³¨İÄŞ³‚Ì»²½Ş
#define MAPWINDOW_SIZE_X GRIDSIZE * 6
#define MAPWINDOW_SIZE_Y 214

// Map‚Ì¸Ş×Ì¨¯¸‚Ì»²½Ş
#define MAPSIZE_X	12000
#define MAPSIZE_Y	8640


// player‚Ìæ‚ª•Ç‚©“¹‚©
enum PASSAGE
{
	PASSAGE_WAY,	// “¹
	PASSAGE_WALL,	// •Ç
	PASSAGE_MAX
};





using namespace std;

class Camera;

class Map
{
public:
	static Map &getIns(void)
	{
		static Map mapins;
		return mapins;
	}
	// Map‚ÌµÌŞ¼Şª¸Ä‚Ì•`‰æ
	void Draw(bool is_edit, VECTOR2 scale,int pCnt,PLAYER tNum,VECTOR2 c_pos);

	// Map‚ÌGrid‚Ì•\¦(Ï½Šm”F—p) gameF:¹Ş°Ñ¼°İ‚ÉˆÚs‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚© true:GameScene false:EditScene
	void MapDraw(bool gameF);

	// Ï¯Ìß‚Ì‘S‘Ì‚ğ‚Æ‚è‚ ‚¦‚¸WALL(•Ç)‚Å‰Šú‰»
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

	// Še•Ï”‚Ì‰Šú‰»ŠÖ”
	bool Init(void);

	// ŠeÌßÚ²Ô°‚ÌÃŞ¨½ÌßÚ²¶¬ŠÖ”
	void CreateIndividualsDisplay(VECTOR2 ind_pos);

	void CreateMap(void);

	// ŠeÌßÚ²Ô°‚ÌÃŞ¨½ÌßÚ²‚Ì•`‰æŠÖ”
	void IndividualsDraw(bool gameF,PLAYER tNum,int pCnt,VECTOR2 c_pos);

	// ‰æ–Ê‚Ì¾¯Ä
	void setUp(const VECTOR2& size, const VECTOR2& chipSize);

	bool setMapData(const VECTOR2 pos, objID id);
	objID GetMapData(const VECTOR2 pos);



	//	ÃŞ°À¾°ÌŞŠÖ”
	bool SaveMap(void);
	//	ÃŞ°ÀÛ°ÄŞŠÖ”
	bool LoadMap(WeakList weaklist,bool loadF);

	
	// Map‚Ì»²½Şæ“¾
	VECTOR2 GetMapSize(void)
	{
		return VECTOR2(MAPSIZE_X, MAPSIZE_Y);
	}
	// ˆêÏ½‚Ì»²½Ş‚Ìæ“¾
	VECTOR2 GetGridSize(void)
	{
		return VECTOR2(GRIDSIZE, GRIDSIZE);
	}
	// Šg‘åk¬‚µ‚½‚©‚ÌÌ×¸Ş‚Ìæ“¾
	bool Get_isScale(void)
	{
		return is_scale;
	}



	// ŒÂ•Ê‚ÌÏ¯Ìß³¨İÄŞ³‚ÌÎß¼Ş¼®İŒvZŠÖ”
	//VECTOR2 IndividualsMapCalcPos(VECTOR2 pos,VECTOR2 camera,VECTOR2 indPos);

	// ¾¯Ä‚µ‚½µÌŞ¼Şª¸Ä‚Ì•`‰æ(num:1P 2P or 3P is_edit:´ÃŞ¨¯ÄÓ°ÄŞ‚©‚Ç‚¤‚©‚ÌÌ×¸Ş scale:Ï¯Ìß‚ÌŠg‘åk¬—¦)
	bool SetObj(VECTOR2 scale,bool is_edit,WeakList weaklist);

	// Map‚ÌŠg‘åk¬(EditScene‚Ì‚İ)
	bool ChangeEditMapScale(Controller ctrl);
	// Map‚ÌŠg‘åk¬—¦‚ÌŒˆ’èŠÖ”(GameScene‚Ì‚İ)
	bool ChangePreyMapScale(void);

	// ÌßÚ²l”‚É‚æ‚Á‚ÄÌßÚ²Ô°‚Ì²İ½Àİ½”‚ğ§ŒÀ
	bool ChangeInstanceCnt(void);
	// Map‚ÌŠg‘åk¬—¦
	VECTOR2 mapScaleCnt;
	// ‚»‚ê‚¼‚ê‚ÌÁ¯Ìß‚ÌŠg‘åk¬—¦
	VECTOR2 blockScaleCnt;


	// ÃŞ¨½ÌßÚ²‚É‰f‚Á‚Ä‚¢‚é©•ªˆÈŠO‚Ì‘¼‚ÌÌßÚ²Ô°‚Ì•`‰æŠÖ”
	void OtherPreyDraw(int ImageName,VECTOR2 indPos,int pCnt);
	
	// ·¬×¸À°‚ğ¶¬‚µ‚½‡”Ô(1=1P 2 =2P 3 =3P)
	int playerCnt;

	std::vector<Camera> camera;

private:
	Map();
	~Map();


	// ¶°¿Ù‚ÌÎß¼Ş¼®İ•â³‚Ì‚½‚ß‚Ì¶Ò×Îß¼Ş¼®İ
	//VECTOR2 cameraPos[PREY_MAX];

	// Map‚ğŠg‘åk¬‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ÌÌ×¸Ş
	bool is_scale;

	// Ï¯Ìß‚Ì‰æ‘œ
	int MapImage;

	// ‘S‘Ì‚ÌÏ¯Ìß‰æ‘œ
	int mapAllwindow;

	// ¦”p~—\’è
	int preyWindow;
	
	// Še³¨İÄŞ³A‘S‘ÌÏ¯Ìß‚Ì•`‰æ§ŒäÌ×¸Ş
	bool is_mapCreate;

	// ¦”p~—\’è
	bool is_preyWindowCreate;

	// Ï¯Ìßê—p‚Ì³¨İÄŞ³
	int MapWindow;

	// ƒQ[ƒ€‰æ–Ê‚ğ•ªŠ„‚µ‚½Û‚Ì•ªŠ„‰ñ”X²
	int windowsNumX;
	// ƒQ[ƒ€‰æ–Ê‚ğ•ªŠ„‚µ‚½Û‚Ì•ªŠ„‰ñ”Y²
	int windowsNumY;

	// ½¸Ø°İ‘S‘Ì‚Ì»²½Ş
	VECTOR2 Scr;
	// ÌßÚ²Ô°²İ½Àİ½Ì×¸Ş(ŒJ‚è•Ô‚µ²İ½Àİ½‚Ì–h~)
	bool is_makePrey[PREY_3];

	// ÌßÚ²Ô°‚Ì²İ½Àİ½”‚Ì§ŒÀ¶³İÄ
	int instanceCnt;




	// Ï¯Ìß‚Ì1Ï½1Ï½‚ÌÃŞ°À
	std::vector<objID*>MapData;
	// Ï¯Ìß‚Ì‘S‘Ì‚ÌÃŞ°À
	std::vector<objID>BaseMap;
	

	// Ï¯Ìß‚ğÁ¯Ìß’PˆÊ‚Å•\‚µ‚½»²½Ş
	VECTOR2 MapSize;
	// 1Á¯Ìß‚Ì»²½Ş
	VECTOR2 ChipSize;
	
	// “¹‚©•Ç‚©‚ÌÌ×¸Ş
	PASSAGE passageF[GRIDCNT_X * GRIDCNT_Y];

	// Ï¯Ìß’PˆÊ‚Ìprey‚Ì²İ½Àİ½Ì×¸Ş
	// “¯‚¶‚Æ‚±‚ë‚É‚Í²İ½Àİ½‚µ‚½‚­‚È‚¢‚½‚ß

	bool makingPreyFlag[MAPSIZE_X / GRIDSIZE][MAPSIZE_Y / GRIDSIZE];
	

	

	//	ˆø”‚Ì‚Æ‚±‚ë‚Å’u‚«Š·‚¦‚½Œ^‚ÅéŒ¾‚·‚é‚Æ‚¢‚¤‚±‚Æ
	template<typename MapType, typename IDType>
	// Map‚ÉÁ¯Ìßî•ñ‚ğ–„‚ß‚ŞŠÖ”
	bool setData(MapType maptype, const VECTOR2 pos, IDType id);

	// Ï¯Ìß‚Ìî•ñ‚ğæ“¾
	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2 pos, IDType defID);
};



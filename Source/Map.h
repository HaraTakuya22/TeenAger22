#pragma once
#include <vector>

#include "Obj.h"

#include "Controller.h"
#include "VECTOR2.h"
#include "AddList.h"
#include "objID.h"
//#include "Prey.h"



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


// l”‚É‰‚¶‚Ämode‚ğ•ÏX
enum PLAYER
{
	PLAYER_IT,		// ‹Sƒ‚[ƒh
	PLAYER_1,		// 1l
	PLAYER_2,		// 2l
	PLAYER_3,		// 3l
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
	// Map‚ÌµÌŞ¼Şª¸Ä‚Ì•`‰æ
	void Draw(void);

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

	// Še•Ï”‚Ì‰Šú‰»ŠÖ”
	bool Init(void);

	// ŠeÌßÚ²Ô°‚ÌÃŞ¨½ÌßÚ²¶¬ŠÖ”
	void CreateIndividualsDisplay(void);

	// ŠeÌßÚ²Ô°‚ÌÃŞ¨½ÌßÚ²‚Ì•`‰æŠÖ”
	void IndividualsDraw(WeakList weaklist,bool gameF);

	// ‰æ–Ê‚Ì¾¯Ä
	void setUp(const VECTOR2& size, const VECTOR2& chipSize);

	bool setMapData(const VECTOR2* pos, objID id);
	objID GetMapData(const VECTOR2* pos);

	//	ÃŞ°À¾°ÌŞŠÖ”
	bool SaveMap(void);
	//	ÃŞ°ÀÛ°ÄŞŠÖ”
	bool LoadMap(void);

	// Ï¯Ìß‚ÌÎß¼Ş¼®İæ“¾
	VECTOR2& GetMapPos(void)
	{
		return mapPos[typeNum];
	}
	VECTOR2& GetIndividualsmapPos(void)
	{
		return individualsMapPos[typeNum];
	}
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

	// ¶°¿Ù‚ÌcameraÎß¼Ş¼®İ‚Ìæ“¾
	VECTOR2 GetCamera(void)
	{
		return cameraPos;
	}

	// Ï¯Ìß‚ÌÎß¼Ş¼®İŒvZŠÖ”
	VECTOR2 MapCalcPos(VECTOR2* c_pos,VECTOR2 scroll);

	// ŒÂ•Ê‚ÌÏ¯Ìß³¨İÄŞ³‚ÌÎß¼Ş¼®İŒvZŠÖ”
	VECTOR2& IndividualsMapCalcPos(VECTOR2* pos,VECTOR2 camera);

	

	// ¾¯Ä‚µ‚½µÌŞ¼Şª¸Ä‚Ì•`‰æ
	bool SetObj(VECTOR2 scale,bool is_edit);

	// Map‚ÌŠg‘åk¬(EditScene‚Ì‚İ)
	bool ChangeEditMapScale(Controller ctrl);
	// Map‚ÌŠg‘åk¬—¦‚ÌŒˆ’èŠÖ”(GameScene‚Ì‚İ)
	bool ChangePreyMapScale(void);
	// Map‚ÌŠg‘åk¬—¦
	VECTOR2 mapScaleCnt;
	// ‚»‚ê‚¼‚ê‚ÌÁ¯Ìß‚ÌŠg‘åk¬—¦
	VECTOR2 blockScaleCnt;

	// ÌßÚ²Ô°‚Ìl”‚ÌŠi”[•Ï”
	PLAYER player;
	TYPE_NUM typeNum;
private:
	Map();
	~Map();

	VECTOR2 setPos;

	// Ï¯Ìß‚Ì¶ã‚ÌÎß¼Ş¼®İ
	VECTOR2 mapPos[PREY_MAX];

	// ÌßÚ²Ô°–ˆ‚ÌÏ¯Ìß‰æ–Ê‚ÌÎß¼Ş¼®İ
	VECTOR2 individualsMapPos[PREY_MAX];

	// ¶°¿Ù‚ÌÎß¼Ş¼®İ•â³‚Ì‚½‚ß‚Ì¶Ò×Îß¼Ş¼®İ
	VECTOR2 cameraPos;
	// Map‚ğŠg‘åk¬‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ÌÌ×¸Ş
	bool is_scale;

	// Ï¯Ìß‚Ì‰æ‘œ
	int MapImage;

	// ‘S‘Ì‚ÌÏ¯Ìß‰æ‘œ
	int mapAllwindow;

	int preyWindow;
	
	// Še³¨İÄŞ³A‘S‘ÌÏ¯Ìß‚Ì•`‰æ§ŒäÌ×¸Ş
	bool is_mapCreate;
	bool is_preyWindowCreate;

	// Ï¯Ìßê—p‚Ì³¨İÄŞ³
	int MapWindow;

	// ƒQ[ƒ€‰æ–Ê‚ğ•ªŠ„‚µ‚½Û‚Ì•ªŠ„‰ñ”X²
	int windowsNumX;
	// ƒQ[ƒ€‰æ–Ê‚ğ•ªŠ„‚µ‚½Û‚Ì•ªŠ„‰ñ”Y²
	int windowsNumY;

	// ½¸Ø°İ‘S‘Ì‚Ì»²½Ş
	VECTOR2 Scr;



	// Ï¯Ìß‚Ì1Ï½1Ï½‚ÌÃŞ°À
	std::vector<objID*>MapData;
	// Ï¯Ìß‚Ì‘S‘Ì‚ÌÃŞ°À
	std::vector<objID>BaseMap;
	

	// 
	VECTOR2 MapSize;
	// 1Á¯Ìß‚Ì»²½Ş
	VECTOR2 ChipSize;
	
	// “¹‚©•Ç‚©‚ÌÌ×¸Ş
	PASSAGE passageF[GRIDCNT_X * GRIDCNT_Y];


	// ÌßÚ²Ô°²İ½Àİ½Ì×¸Ş(ŒJ‚è•Ô‚µ²İ½Àİ½‚Ì–h~)
	bool is_makePrey;

	// ‹S‚Ì²İ½Àİ½Ì×¸Ş(ŒJ‚è•Ô‚µ²İ½Àİ½‚Ì–h~)
	bool is_makeIt;

	//	ˆø”‚Ì‚Æ‚±‚ë‚Å’u‚«Š·‚¦‚½Œ^‚ÅéŒ¾‚·‚é‚Æ‚¢‚¤‚±‚Æ
	template<typename MapType, typename IDType>
	// Map‚ÉÁ¯Ìßî•ñ‚ğ–„‚ß‚ŞŠÖ”
	bool setData(MapType maptype, const VECTOR2* pos, IDType id);

	template<typename MapType, typename IDType>
	IDType GetData(MapType maptype, const VECTOR2& pos, IDType defID);
};



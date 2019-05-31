#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"
#include "Camera.h"

// ‹S‚¶‚á‚È‚¢‘¤‚Ì»²½Ş(Prey = ’Ç‚í‚ê‚é‚à‚Ì)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ÌßÚ²Ô°‚Ì½Ëß°ÄŞ
#define SPEED			GRIDSIZE

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos,TYPE_NUM pNum,PLAYER num,VECTOR2 camera);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ÌßÚ²Ô°‚Ì•`‰æ
	void Draw(void);
	// À²Ìß‚Ìó‚¯æ‚è
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	// ·¬×¶¬‚ÌÛ‚Ì·¬×‚ÌÀ²Ìß‚Ìæ“¾
	TYPE_NUM GetTypeNum(void) 
	{
		return typeObjNum;
	}
	// 1P 2P 3P ‚Ìî•ñæ“¾
	PLAYER& GetPlayerNum(void)
	{
		return player;
	}
	// individualsMapPos‚Ìæ“¾
	/*VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}*/

private:
	bool Init(TYPE_NUM p_num);

	// Še·¬×‚Ì±ÆÒ°¼®İ‚Ì‰Šú‰»
	bool AnimInit(void);
};


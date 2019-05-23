#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"

// ‹S‚¶‚á‚È‚¢‘¤‚Ì»²½Ş(Prey = ’Ç‚í‚ê‚é‚à‚Ì)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ÌßÚ²Ô°‚Ì½Ëß°ÄŞ
#define SPEED			GRIDSIZE
// ±ÆÒ°¼®İºÏ”
#define ANIMATION_MAX	4

typedef struct {
	int		image[DIR_MAX][ANIMATION_MAX];	// ÌßÚ²Ô°‰æ‘œID
	bool	Flag;							// ÌßÚ²Ô°‚Ìó‘Ô
	int		animation;						// ±ÆÒ°¼®İ
}CHARACTER;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos,TYPE_NUM pNum);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ÌßÚ²Ô°‚Ì•`‰æ
	void Draw(void);
	// À²Ìß‚Ìó‚¯æ‚è
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	// typeNum(¡Œ»İ²İ½Àİ½‚³‚ê‚Ä‚¢‚éÌßÚ²Ô°‚ª1p‚È‚Ì‚©)‚Ìæ“¾
	TYPE_NUM& GetTypeNum(void)
	{
		return typeNum;
	}
	// mapPos‚Ìæ“¾
	VECTOR2& GetMapPos(void)
	{
		return mapPos;
	}
	// individualsMapPos‚Ìæ“¾
	VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}

private:
	bool Init(TYPE_NUM p_num);
	CHARACTER player[PLAYER_MAX];
	int animID[PREY_MAX];
};


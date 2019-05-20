#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"

// ‹S‚¶‚á‚È‚¢‘¤‚Ì»²½Þ(Prey = ’Ç‚í‚ê‚é‚à‚Ì)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ÌßÚ²Ô°‚Ì½Ëß°ÄÞ
#define SPEED			GRIDSIZE

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2* pos,TYPE_NUM pNum);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ÌßÚ²Ô°‚Ì•`‰æ
	void Draw(void);
	// À²Ìß‚ÌŽó‚¯Žæ‚è
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(TYPE_NUM p_num);
};


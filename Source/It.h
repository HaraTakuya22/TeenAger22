#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"

// ‹S‘¤‚Ì»²½Þ(It = ’Ç‚¤‚à‚Ì)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ÌßÚ²Ô°‚Ì½Ëß°ÄÞ
#define SPEED			GRIDSIZE

class It :
	public Obj
{
public:
	It();
	It(VECTOR2* pos, TYPE_NUM i_num);
	~It();
	void Draw(void);
	void Move(const Controller& controll, WeakList objlist);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_IT);
	}

private:
	bool Init(TYPE_NUM i_num);
};


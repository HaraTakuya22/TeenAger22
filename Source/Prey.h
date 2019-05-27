#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"

// 鬼じゃない側のｻｲｽﾞ(Prey = 追われるもの)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
#define SPEED			GRIDSIZE

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos,TYPE_NUM pNum,int num);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ﾌﾟﾚｲﾔｰの描画
	void Draw(void);
	// ﾀｲﾌﾟの受け取り
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	TYPE_NUM GetTypeNum(void) 
	{
		return typeObjNum;
	}
	int GetPlayerCnt(void)
	{
		return playerCnt;
	}
	// individualsMapPosの取得
	VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}

private:
	bool Init(TYPE_NUM p_num);
};


#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"
#include "Camera.h"

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
	Prey(VECTOR2 pos,TYPE_NUM pNum,PLAYER num,VECTOR2 camera);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ﾌﾟﾚｲﾔｰの描画
	void Draw(void);
	// ﾀｲﾌﾟの受け取り
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	// ｷｬﾗ生成の際のｷｬﾗのﾀｲﾌﾟの取得
	TYPE_NUM GetTypeNum(void) 
	{
		return typeObjNum;
	}
	// 1P 2P 3P の情報取得
	PLAYER& GetPlayerNum(void)
	{
		return player;
	}
	// individualsMapPosの取得
	/*VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}*/

private:
	bool Init(TYPE_NUM p_num);

	// 各ｷｬﾗのｱﾆﾒｰｼｮﾝの初期化
	bool AnimInit(void);
};


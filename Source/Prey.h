#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"

// 鬼じゃない側のｻｲｽﾞ(Prey = 追われるもの)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
#define SPEED			GRIDSIZE
// ｱﾆﾒｰｼｮﾝｺﾏ数
#define ANIMATION_MAX	4

typedef struct {
	int		image[DIR_MAX][ANIMATION_MAX];	// ﾌﾟﾚｲﾔｰ画像ID
	bool	Flag;							// ﾌﾟﾚｲﾔｰの状態
	int		animation;						// ｱﾆﾒｰｼｮﾝ
}CHARACTER;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos,TYPE_NUM pNum);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ﾌﾟﾚｲﾔｰの描画
	void Draw(void);
	// ﾀｲﾌﾟの受け取り
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	// typeNum(今現在ｲﾝｽﾀﾝｽされているﾌﾟﾚｲﾔｰが1pなのか)の取得
	TYPE_NUM& GetTypeNum(void)
	{
		return typeNum;
	}
	// mapPosの取得
	VECTOR2& GetMapPos(void)
	{
		return mapPos;
	}
	// individualsMapPosの取得
	VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}

private:
	bool Init(TYPE_NUM p_num);
	CHARACTER player[PLAYER_MAX];
	int animID[PREY_MAX];
};


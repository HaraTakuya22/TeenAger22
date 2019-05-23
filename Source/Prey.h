#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>

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
	Prey(VECTOR2* pos, TYPE_NUM p_num);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ﾌﾟﾚｲﾔｰの描画
	void Draw(void);
	// ﾀｲﾌﾟの受け取り
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(TYPE_NUM pNum);

	CHARACTER player[PLAYER_MAX];
	int animID[PREY_MAX];
};


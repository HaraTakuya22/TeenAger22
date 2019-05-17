#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>


// 鬼じゃない側のｻｲｽﾞ(Prey = 追われるもの)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
#define SPEED			GRIDSIZE
// ﾌﾟﾚｲﾔｰ数
#define PLAYER_MAX		3
// ｱﾆﾒｰｼｮﾝｺﾏ数
#define ANIMATION_MAX	4

enum TBL_ID {
	TBL_MAIN,
	TBL_SUB,
	TBL_MAX,
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,
	DIR_TBL_OPP,
	DIR_TBL_SUB1,
	DIR_TBL_SUB2,
	DIR_TBL_MAX,
};

enum  SIDE_CHECK {
	OUT_SIDE,
	IN_SIDE,
	SIDE_MAX
};

typedef struct {
	int		image[DIR_MAX][ANIMATION_MAX];	// ﾌﾟﾚｲﾔｰ画像ID
	VECTOR2 pos[PREY_MAX];					// ﾌﾟﾚｲﾔｰ座標
	bool	Flag;							// ﾌﾟﾚｲﾔｰの状態
	int		animation;						// ｱﾆﾒｰｼｮﾝ
	DIR		dir;							// ﾌﾟﾚｲﾔｰの方向
}CHARACTER;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos, PREY_NUM p_num);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	void Draw(void);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(PREY_NUM p_num);

	CHARACTER charimage[PREY_MAX];
	CHARACTER player[PLAYER_MAX];
};


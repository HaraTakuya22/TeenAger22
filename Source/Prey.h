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
	// ﾌﾟﾚｲﾔｰの描画
	void Draw(void);
	// ﾀｲﾌﾟの受け取り
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(PREY_NUM p_num);

	CHARACTER charimage[PREY_MAX];
	CHARACTER player[PLAYER_MAX];

};


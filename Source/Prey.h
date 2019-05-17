#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>


// ãSÇ∂Ç·Ç»Ç¢ë§ÇÃª≤Ωﬁ(Prey = í«ÇÌÇÍÇÈÇ‡ÇÃ)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// Ãﬂ⁄≤‘∞ÇÃΩÀﬂ∞ƒﬁ
#define SPEED			GRIDSIZE
// Ãﬂ⁄≤‘∞êî
#define PLAYER_MAX		3
// ±∆“∞ºÆ›∫œêî
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
	int		image[DIR_MAX][ANIMATION_MAX];	// Ãﬂ⁄≤‘∞âÊëúID
	VECTOR2 pos[PREY_MAX];					// Ãﬂ⁄≤‘∞ç¿ïW
	bool	Flag;							// Ãﬂ⁄≤‘∞ÇÃèÛë‘
	int		animation;						// ±∆“∞ºÆ›
	DIR		dir;							// Ãﬂ⁄≤‘∞ÇÃï˚å¸
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


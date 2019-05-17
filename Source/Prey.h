#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>

// ‹S‚¶‚á‚È‚¢‘¤‚Ì»²½Ş(Prey = ’Ç‚í‚ê‚é‚à‚Ì)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ÌßÚ²Ô°‚Ì½Ëß°ÄŞ
#define SPEED			GRIDSIZE
// ÌßÚ²Ô°”
#define PLAYER_MAX		3
// ±ÆÒ°¼®İºÏ”
#define ANIMATION_MAX	4

typedef struct {
	int		image[DIR_MAX][ANIMATION_MAX];	// ÌßÚ²Ô°‰æ‘œID
	VECTOR2 pos[PREY_MAX];					// ÌßÚ²Ô°À•W
	bool	Flag;							// ÌßÚ²Ô°‚Ìó‘Ô
	int		animation;						// ±ÆÒ°¼®İ
	DIR		dir;							// ÌßÚ²Ô°‚Ì•ûŒü
}CHARACTER;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos, PREY_NUM p_num);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ÌßÚ²Ô°‚Ì•`‰æ
	void Draw(void);
	// À²Ìß‚Ìó‚¯æ‚è
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(PREY_NUM p_num);

	CHARACTER charimage[PREY_MAX];
	CHARACTER player[PLAYER_MAX];

};


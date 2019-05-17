#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2 pos, PREY_NUM p_num)
{
	
	// playerÇÃŒﬂºﬁºÆ›ÇÃæØƒ
	//SetPos(pos);
	Prey::Init(p_num);
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].Flag = true;
		player[i].animation = 0;
	}
	player[0].pos[PREY_1].x = GRIDSIZE * 3;
	player[0].pos[PREY_1].y = GRIDSIZE * 4;
	player[0].dir = DIR_DOWN;
	player[1].dir = DIR_DOWN;
}


Prey::~Prey()
{
}

void Prey::Move(const Controller & controll, WeakList objlist)
{
	auto mapSize = lpMap.GetMapSize();
	auto gridSize = lpMap.GetGridSize().x;
	auto Scr = lpScene.GetScrSize();

	auto input = controll.GetButtonInfo(KEY_TYPE_NOW);
	auto inputOld = controll.GetButtonInfo(KEY_TYPE_OLD);

	// à⁄ìÆèàóù(MapÇÃà⁄ìÆ & Ãﬂ⁄≤‘∞ÇÃà⁄ìÆ)-----------------------------
	// âEà⁄ìÆ
	if (input[KEY_INPUT_NUMPAD6] & ~inputOld[KEY_INPUT_NUMPAD6])
	{
		if (lpMap.GetMapPos().x > -(mapSize.x - GRIDSIZE * 6))
		{
			player[0].pos[PREY_1].x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
			lpMap.individualsMapPos.x += GRIDSIZE;
			player[0].dir = DIR_RIGHT;
			player[0].animation++;
		}
	}

	// ç∂à⁄ìÆ
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < GRIDSIZE * 3)
		{
			player[0].pos[PREY_1].x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
			lpMap.individualsMapPos.x -= GRIDSIZE;
			player[0].dir = DIR_LEFT;
			player[0].animation++;
		}
	}
	// è„à⁄ìÆ
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < GRIDSIZE * 3)
		{
			player[0].pos[PREY_1].y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
			lpMap.individualsMapPos.y -= GRIDSIZE;
			player[0].dir = DIR_UP;
			player[0].animation++;
		}
	}
	// â∫à⁄ìÆ
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -(mapSize.y - GRIDSIZE * 6))
		{
			player[0].pos[PREY_1].y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
			lpMap.individualsMapPos.y += GRIDSIZE;
			player[0].dir = DIR_DOWN;
			player[0].animation++;
		}
	}


	//----------------------------------------------------------------------------

	// ÅñÃﬂ⁄≤‘∞ÇÃŒﬂºﬁºÆ›Çë´å≥Ç…ê›íËÇ∑ÇÈÅB

	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", player[0].pos[PREY_1].x, player[0].pos[PREY_1].y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();

	const char *imageList[PREY_MAX] = {
		{"character/character1.png" },
		{"character/character2.png"},
	};

	for (int i = 0; i < PREY_MAX; i++)
	{
		LoadDivGraph(imageList[i], DIR_MAX * ANIMATION_MAX, ANIMATION_MAX, DIR_MAX, PREYSIZE_X, PREYSIZE_Y, &charimage[i].image[0][0]);
	}
	
}

bool Prey::Init(PREY_NUM p_num)
{
	int animID = (player[0].animation / 1) % ANIMATION_MAX;

	if (p_num == PREY_1)
	{
		DrawGraph(GRIDSIZE * 3, GRIDSIZE * 4 - 40, charimage[PREY_1].image[player[0].dir][animID], true);
	}
	if (p_num == PREY_2)
	{
		Obj::Init("character/character2.png", VECTOR2(4, 4), VECTOR2(320 / 4, 480 / 4));
	}
	
	lpMap.IndividualsMapCalcPos(pos, player_cameraPos);

	return true;
}

#include <DxLib.h>
#include "Scene.h"
#include "Prey.h"
#include "Controller.h"
#include "Image.h"



Prey::Prey()
{
}

Prey::Prey(VECTOR2* pos, TYPE_NUM pNum)
{

	Prey::Init(pNum);

	SetPos(&pos[pNum]);
	AniCnt[pNum] = 0;

	dir[PREY_1] = DIR_DOWN;
	dir[PREY_2] = DIR_DOWN;
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
		if (lpMap.GetMapPos().x > -(mapSize.x - GRIDSIZE * 5))
		{
			pos[PREY_1].x += SPEED;
			lpMap.GetMapPos().x -= SPEED;
			lpMap.GetIndividualsmapPos().x += SPEED;
			dir[PREY_1] = DIR_RIGHT;
			AniCnt[PREY_1]++;
		}
	}
	// ç∂à⁄ìÆ
	if (input[KEY_INPUT_NUMPAD4] & ~inputOld[KEY_INPUT_NUMPAD4])
	{
		if (lpMap.GetMapPos().x < GRIDSIZE * 2)
		{
			pos[PREY_1].x -= SPEED;
			lpMap.GetMapPos().x += SPEED;
			lpMap.GetIndividualsmapPos().x -= SPEED;
			dir[PREY_1] = DIR_LEFT;
			AniCnt[PREY_1]++;
		}
	}
	// è„à⁄ìÆ
	if (input[KEY_INPUT_NUMPAD8] & ~inputOld[KEY_INPUT_NUMPAD8])
	{
		if (lpMap.GetMapPos().y < GRIDSIZE * 3)
		{
			pos[PREY_1].y -= SPEED;
			lpMap.GetMapPos().y += SPEED;
			lpMap.GetIndividualsmapPos().y -= GRIDSIZE;
			dir[PREY_1] = DIR_UP;
			AniCnt[PREY_1]++;
		}
	}
	// â∫à⁄ìÆ
	if (input[KEY_INPUT_NUMPAD2] & ~inputOld[KEY_INPUT_NUMPAD2])
	{
		if (lpMap.GetMapPos().y > -(mapSize.y - GRIDSIZE * 6))
		{
			pos[PREY_1].y += SPEED;
			lpMap.GetMapPos().y -= SPEED;
			lpMap.GetIndividualsmapPos().y += GRIDSIZE;
			dir[PREY_1] = DIR_DOWN;
			AniCnt[PREY_1]++;
		}
	}

	//// âEà⁄ìÆ
	//if (input[KEY_INPUT_D] & ~inputOld[KEY_INPUT_D])
	//{
	//	if (lpMap.GetMapPos().x > -(mapSize.x - GRIDSIZE * 5))
	//	{
	//		pos[PREY_2].x += SPEED;
	//		lpMap.GetMapPos().x -= SPEED;
	//		lpMap.GetIndividualsmapPos().x += SPEED;
	//		dir[PREY_2] = DIR_RIGHT;
	//		AniCnt[PREY_2]++;
	//	}
	//}
	//// ç∂à⁄ìÆ
	//if (input[KEY_INPUT_A] & ~inputOld[KEY_INPUT_A])
	//{
	//	if (lpMap.GetMapPos().x < GRIDSIZE * 2)
	//	{
	//		pos[PREY_2].x -= SPEED;
	//		lpMap.GetMapPos().x += SPEED;
	//		lpMap.GetIndividualsmapPos().x -= SPEED;
	//		dir[PREY_2] = DIR_LEFT;
	//		AniCnt[PREY_2]++;
	//	}
	//}
	//// è„à⁄ìÆ
	//if (input[KEY_INPUT_W] & ~inputOld[KEY_INPUT_W])
	//{
	//	if (lpMap.GetMapPos().y < GRIDSIZE * 3)
	//	{
	//		pos[PREY_2].y -= SPEED;
	//		lpMap.GetMapPos().y += SPEED;
	//		lpMap.GetIndividualsmapPos().y -= GRIDSIZE;
	//		dir[PREY_2] = DIR_UP;
	//		AniCnt[PREY_2]++;
	//	}
	//}
	//// â∫à⁄ìÆ
	//if (input[KEY_INPUT_S] & ~inputOld[KEY_INPUT_S])
	//{
	//	if (lpMap.GetMapPos().y > -(mapSize.y - GRIDSIZE * 6))
	//	{
	//		pos[PREY_2].y += SPEED;
	//		lpMap.GetMapPos().y -= SPEED;
	//		lpMap.GetIndividualsmapPos().y += GRIDSIZE;
	//		dir[PREY_2] = DIR_DOWN;
	//		AniCnt[PREY_2]++;
	//	}
	//}

	//----------------------------------------------------------------------------

	// ÅñÃﬂ⁄≤‘∞ÇÃŒﬂºﬁºÆ›Çë´å≥Ç…ê›íËÇ∑ÇÈÅB


	_RPTN(_CRT_WARN, "character.pos:%d,%d\n", pos[PREY_1].x, pos[PREY_1].y);
	_RPTN(_CRT_WARN, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

void Prey::Draw(void)
{
	Obj::Draw();

	animID[PREY_1] = (AniCnt[PREY_1] / 1) % ANIMATION_MAX;
	animID[PREY_2] = (AniCnt[PREY_2] / 1) % ANIMATION_MAX;
	player_cameraPos[PREY_1] = { 240,280 };
	player_cameraPos[PREY_2] = { 880,280 };

	//if (typeNum == PREY_1)
	{
		DrawGraph(player_cameraPos[PREY_1].x, player_cameraPos[PREY_1].y, player[PREY_1].image[dir[PREY_1]][animID[PREY_1]], true);
	}
	if (typeNum == PREY_2)
	{
		DrawGraph(player_cameraPos[PREY_2].x, player_cameraPos[PREY_2].y, player[PREY_2].image[dir[PREY_2]][animID[PREY_2]], true);
	}
	DrawFormatString(0, 0, 0xffffff, "character.pos:%d,%d\n", pos[PREY_1].x, pos[PREY_1].y);
	DrawFormatString(0, 20, 0xffffff, "map.pos:%d,%d\n", lpMap.GetMapPos().x, lpMap.GetMapPos().y);
}

bool Prey::Init(TYPE_NUM pNum)
{
	lpMap.IndividualsMapCalcPos(&pos[pNum], player_cameraPos[pNum]);

	if (pNum == PREY_1)
	{
		LoadDivGraph("character/character.png", DIR_MAX * ANIMATION_MAX, ANIMATION_MAX, DIR_MAX, PREYSIZE_X, PREYSIZE_Y, &player[PREY_1].image[0][0]);
	}
	if (pNum == PREY_2)
	{
		LoadDivGraph("character/character2.png", DIR_MAX * ANIMATION_MAX, ANIMATION_MAX, DIR_MAX, PREYSIZE_X, PREYSIZE_Y, &player[PREY_2].image[0][0]);
	}

	return true;
}

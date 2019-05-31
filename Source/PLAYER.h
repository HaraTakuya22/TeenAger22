#pragma once


enum class PLAYER
{
	CURSOR,
	PLAYER_1,		// 1�l
	PLAYER_2,		// 2�l
	PLAYER_3,		// 3�l
	PLAYER_IT,		// �S
	PLAYER_MAX
};

PLAYER begin(PLAYER);
PLAYER end(PLAYER);
PLAYER operator++(PLAYER &p);
PLAYER operator+(PLAYER &p, int k);
PLAYER operator-(PLAYER &p, int k);
PLAYER operator*(PLAYER &p);
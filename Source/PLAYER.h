#pragma once


enum class PLAYER
{
	CURSOR,
	PLAYER_1,		// 1êl
	PLAYER_2,		// 2êl
	PLAYER_3,		// 3êl
	PLAYER_IT,		// ãS
	PLAYER_MAX
};

PLAYER begin(PLAYER);
PLAYER end(PLAYER);
PLAYER operator++(PLAYER &p);
PLAYER operator+(PLAYER &p, int k);
PLAYER operator-(PLAYER &p, int k);
PLAYER operator*(PLAYER &p);
#include <type_traits>

#include "PLAYER.h"

//PLAYERの先頭の要素を返してあげる
PLAYER begin(PLAYER)
{
	return PLAYER::CURSOR;
}

//NUM_TYPEの末端が返ってくる
PLAYER end(PLAYER)
{
	//NONではない。
	//listの中ではMAXが最終となる。
	return PLAYER::PLAYER_MAX;
}

PLAYER operator++(PLAYER & p)
{
	//基底のｸﾗｽを抜き出して、それに対してidに当てはめてそれに1を足す→それをdirに格納
	return p = PLAYER(std::underlying_type<PLAYER>::type(p) + 1);
}

PLAYER operator+(PLAYER & p, int k)
{
	return static_cast<PLAYER>(static_cast<int> (p) + k);
}

PLAYER operator-(PLAYER & p, int k)
{
	return static_cast<PLAYER>(static_cast<int> (p) - k);
}

//自分自身を返す。
PLAYER operator*(PLAYER & p)
{
	return p;
}

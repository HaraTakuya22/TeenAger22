#include <type_traits>
#include "objID.h"

//objIDの先頭の要素を返してあげる
objID begin(objID)
{
	return objID::PLAYER;
}

//objIDの末端が返ってくる
objID end(objID)
{
	//NONではない。
	//listの中ではMAXが最終となる。
	return objID::ID_MAX;
}

objID operator++(objID & id)
{
	//基底のｸﾗｽを抜き出して、それに対してidに当てはめてそれに1を足す→それをdirに格納
	return id = objID(std::underlying_type<objID>::type(id) + 1);
}

objID operator+(objID & id, int k)
{
	return static_cast<objID>(static_cast<int> (id) + k);
}

objID operator-(objID & id, int k)
{
	return static_cast<objID>(static_cast<int> (id) - k);
}

//自分自身を返す。
objID operator*(objID & id)
{
	return id;
}

#include <type_traits>
#include "NUM_TYPE.h"



//NUM_TYPEの先頭の要素を返してあげる
TYPE_NUM begin(TYPE_NUM)
{
	return TYPE_NUM::NUM_CURSOR;
}

//NUM_TYPEの末端が返ってくる
TYPE_NUM end(TYPE_NUM)
{
	//NONではない。
	//listの中ではMAXが最終となる。
	return TYPE_NUM::PREY_MAX;
}

TYPE_NUM operator++(TYPE_NUM & num)
{
	//基底のｸﾗｽを抜き出して、それに対してidに当てはめてそれに1を足す→それをdirに格納
	return num = TYPE_NUM(std::underlying_type<TYPE_NUM>::type(num) + 1);
}

TYPE_NUM operator+(TYPE_NUM & num, int k)
{
	return static_cast<TYPE_NUM>(static_cast<int> (num) + k);
}

TYPE_NUM operator-(TYPE_NUM & num, int k)
{
	return static_cast<TYPE_NUM>(static_cast<int> (num) - k);
}

//自分自身を返す。
TYPE_NUM operator*(TYPE_NUM & num)
{
	return num;
}


#include <type_traits>

#include "PLAYER.h"

//PLAYER�̐擪�̗v�f��Ԃ��Ă�����
PLAYER begin(PLAYER)
{
	return PLAYER::CURSOR;
}

//NUM_TYPE�̖��[���Ԃ��Ă���
PLAYER end(PLAYER)
{
	//NON�ł͂Ȃ��B
	//list�̒��ł�MAX���ŏI�ƂȂ�B
	return PLAYER::PLAYER_MAX;
}

PLAYER operator++(PLAYER & p)
{
	//���̸׽�𔲂��o���āA����ɑ΂���id�ɓ��Ă͂߂Ă����1�𑫂��������dir�Ɋi�[
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

//�������g��Ԃ��B
PLAYER operator*(PLAYER & p)
{
	return p;
}

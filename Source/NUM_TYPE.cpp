#include <type_traits>
#include "NUM_TYPE.h"



//NUM_TYPE�̐擪�̗v�f��Ԃ��Ă�����
TYPE_NUM begin(TYPE_NUM)
{
	return TYPE_NUM::NUM_CURSOR;
}

//NUM_TYPE�̖��[���Ԃ��Ă���
TYPE_NUM end(TYPE_NUM)
{
	//NON�ł͂Ȃ��B
	//list�̒��ł�MAX���ŏI�ƂȂ�B
	return TYPE_NUM::PREY_MAX;
}

TYPE_NUM operator++(TYPE_NUM & num)
{
	//���̸׽�𔲂��o���āA����ɑ΂���id�ɓ��Ă͂߂Ă����1�𑫂��������dir�Ɋi�[
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

//�������g��Ԃ��B
TYPE_NUM operator*(TYPE_NUM & num)
{
	return num;
}


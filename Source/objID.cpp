#include <type_traits>
#include "objID.h"

//FIRE_DIR�̐擪�̗v�f��Ԃ��Ă�����
objID begin(objID)
{
	return objID::FLOOR;
}

//FIRE_DIR�̖��[���Ԃ��Ă���
objID end(objID)
{
	//DOWN�ł͂Ȃ��B
	//list�̒��ł�MAX���ŏI�ƂȂ�B
	return objID::ID_MAX;
}

objID operator++(objID & id)
{
	//���̸׽�𔲂��o���āA����ɑ΂���dir�ɓ��Ă͂߂Ă����1�𑫂��������dir�Ɋi�[
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

//�������g��Ԃ��B
objID operator*(objID & id)
{
	return id;
}

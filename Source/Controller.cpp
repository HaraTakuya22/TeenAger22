#include <DxLib.h>
#include "Controller.h"



Controller::Controller()
{

}


Controller::~Controller()
{

}

bool Controller::Update(void)
{
	//�O�ڰтŉ��������ݏ��
	keyOld = key;
	//�S���݂̉������
	GetHitKeyStateAll(&key[0]);

	return true;
}

const KEY_FLAG & Controller::GetButtonInfo(KEY_TYPE type) const
{
	if (type == OLD)
	{
		return keyOld;
	}
	return key;
}

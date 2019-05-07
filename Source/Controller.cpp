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

	PadInputOld = PadInput;

	//�S���݂̉������
	GetHitKeyStateAll(&key[0]);

	return true;
}

const KEY_FLAG & Controller::GetButtonInfo(KEY_TYPE type) const
{
	if (type == KEY_TYPE_OLD)
	{
		return keyOld;
	}
	return key;
}

const PAD_INPUT & Controller::GetPadButtonInfo(PAD_INPUT inputType) const
{
	if (inputType == PAD_INPUT_OLD)
	{
		return PadInputOld;
	}
	return PadInput;
}

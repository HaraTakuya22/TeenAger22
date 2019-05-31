#include <DxLib.h>
#include "Controller.h"
#include "Camera.h"



Controller::Controller()
{
	for (int i = 0; i < KEY_TYPE_MAX; ++i)
	{
		for (int j = 0; j < CAMERA_MAX; ++j)
		{
			input[i][j] = 0;
		}
	}
}


Controller::~Controller()
{

}

bool Controller::Update(void)
{
	//‘OÌÚ°Ñ‚Å‰Ÿ‚µ‚½ÎÞÀÝî•ñ
	keyOld = key;
	

	PadInputOld = PadInput;

	//‘SÎÞÀÝ‚Ì‰Ÿ‰ºî•ñ

	GetHitKeyStateAll(key.data());

	inputOld = input;


	// 1P‘€ì
	input[KEY_TYPE_NOW][CAMERA_LEFT] = key[KEY_INPUT_LEFT];
	input[KEY_TYPE_NOW][CAMERA_RIGHT] = key[KEY_INPUT_RIGHT];
	input[KEY_TYPE_NOW][CAMERA_UP] = key[KEY_INPUT_UP];
	input[KEY_TYPE_NOW][CAMERA_DOWN] = key[KEY_INPUT_DOWN];

	inputOld[KEY_TYPE_OLD][CAMERA_LEFT] = keyOld[KEY_INPUT_LEFT];
	inputOld[KEY_TYPE_OLD][CAMERA_RIGHT] = keyOld[KEY_INPUT_RIGHT];
	inputOld[KEY_TYPE_OLD][CAMERA_UP] = keyOld[KEY_INPUT_UP];
	inputOld[KEY_TYPE_OLD][CAMERA_DOWN] = keyOld[KEY_INPUT_DOWN];

	// 2P‘€ì
	/*input[KEY_TYPE_NOW][CAMERA_LEFT] = key[KEY_INPUT_LEFT];
	input[KEY_TYPE_NOW][CAMERA_RIGHT] = key[KEY_INPUT_RIGHT];
	input[KEY_TYPE_NOW][CAMERA_UP] = key[KEY_INPUT_UP];
	input[KEY_TYPE_NOW][CAMERA_DOWN] = key[KEY_INPUT_DOWN];

	inputOld[KEY_TYPE_OLD][CAMERA_LEFT] = keyOld[KEY_INPUT_LEFT];
	inputOld[KEY_TYPE_OLD][CAMERA_RIGHT] = keyOld[KEY_INPUT_RIGHT];
	inputOld[KEY_TYPE_OLD][CAMERA_UP] = keyOld[KEY_INPUT_UP];
	inputOld[KEY_TYPE_OLD][CAMERA_DOWN] = keyOld[KEY_INPUT_DOWN];*/


	return true;
}

const KEY_INPUT& Controller::GetButtonInfo(void) const
{
	for (int camera = 0; camera < CAMERA_MAX; camera++)
	{
		if (input[KEY_TYPE_NOW][camera] && !inputOld[KEY_TYPE_OLD][camera])
		{
			return input;
		}
	}
	return inputOld;
}

//const KEY_INPUT & Controller::GetButtonInfo() const
//{
//	/*if (type == KEY_TYPE_OLD)
//	{
//		return inputOld;
//	}*/
//	return input;
//}

const KEY_FLAG & Controller::GetKeyButtonInfo(KEY_TYPE type) const
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

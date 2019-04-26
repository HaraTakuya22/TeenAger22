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
	//‘OÌÚ°Ñ‚Å‰Ÿ‚µ‚½ÎŞÀİî•ñ
	keyOld = key;
	//‘SÎŞÀİ‚Ì‰Ÿ‰ºî•ñ
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

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
	//前ﾌﾚｰﾑで押したﾎﾞﾀﾝ情報
	keyOld = key;
	//全ﾎﾞﾀﾝの押下情報
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

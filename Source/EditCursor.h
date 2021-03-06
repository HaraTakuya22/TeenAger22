#pragma once
#include "Obj.h"


class EditCursor :
	public Obj
{
public:
	EditCursor(VECTOR2 pos,TYPE_NUM num,VECTOR2 camera);
	~EditCursor();
	void Move(const Controller& controll, WeakList objlist);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_CURSOR);
	}
	
	// individualsMapPos取得関数
	//VECTOR2& GetIndividualsMapPos(void)
	//{
	//	return individualsMapPos;
	//}

	PLAYER& GetPlayerNum(void)
	{
		return player;
	}

	VECTOR2 GetCameraPosition(void)
	{
		return cameraPosition;
	}

private:
	void Draw(void);

	// ｶｰｿﾙがﾋﾟｺﾋﾟｺ点滅するｶｳﾝﾄ
	int flickCnt;

	// ｶｰｿﾙの変換ﾎﾞﾀﾝの押下ﾌﾗｸﾞ(id進める)
	int ChangeInput;
	int ChangeInputOld;
	// ｶｰｿﾙの変換ﾎﾞﾀﾝの押下ﾌﾗｸﾞ(id戻す)
	int ChangeInputBack;
	int ChangeInputBackOld;

	// id情報を埋め込むﾎﾞﾀﾝの押下ﾌﾗｸﾞ
	int SetInput;
	int SetInputOld;

	// ﾃｽﾄ用
	bool setF;

	VECTOR2 cursorPos;

	int keyDefRng;
	int inputFrame;

	// ID
	objID id;
};


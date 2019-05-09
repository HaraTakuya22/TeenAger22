#pragma once
#include "Obj.h"

struct SETID
{
	VECTOR2 set_pos;
	objID set_id;
};

class EditCursor :
	public Obj
{
public:
	EditCursor(VECTOR2 pos);
	~EditCursor();
	void Move(const Controller& controll, WeakList objlist);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_CURSOR);
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

	int keyDefRng;
	int inputFrame;

	// ID
	objID id;
	SETID setId;
};


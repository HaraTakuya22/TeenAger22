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

	// ���ق��ߺ�ߺ�_�ł��鶳��
	int flickCnt;

	// ���ق̕ϊ����݂̉����׸�(id�i�߂�)
	int ChangeInput;
	int ChangeInputOld;
	// ���ق̕ϊ����݂̉����׸�(id�߂�)
	int ChangeInputBack;
	int ChangeInputBackOld;

	// id���𖄂ߍ������݂̉����׸�
	int SetInput;
	int SetInputOld;

	// ýėp
	bool setF;

	

	int keyDefRng;
	int inputFrame;

	// ID
	objID id;
	SETID setId;
};


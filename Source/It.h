#pragma once
#include "Obj.h"
class It :
	public Obj
{
public:
	It();
	It(VECTOR2 pos, TYPE_NUM pNum, int num);
	~It();
	void Draw(void);
	void Move(const Controller& controll, WeakList objlist);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_IT);
	}

private:
	bool Init(void);
};


#pragma once
#include "AddList.h"
#include "BaseScene.h"
class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller);

private:

	// initialize
	virtual int Init(void);

	Shared_ObjListptr objlist;
	List_Obj_itr obj;
	void EditDraw(void);

};


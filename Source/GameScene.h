#pragma once
#include "Obj.h"
#include "BaseScene.h"
#include "AddList.h"
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller);

private:
	// initialize
	virtual int Init(void);
	// object's list
	Shared_ObjListptr objlist;

	void Draw(void);

	// ÌßÚ²Ô°²Ý½ÀÝ½Ì×¸Þ(ŒJ‚è•Ô‚µ²Ý½ÀÝ½‚Ì–hŽ~)
	bool is_makePrey;
};


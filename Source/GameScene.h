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

	VECTOR2 preyInstancePos[PREY_3];
	bool is_Instance[PREY_3];

	void Draw(void);

	// ¹Þ°Ñ¼°Ý‚É“ü‚Á‚½Žž‚ÌÀ²Ï°‚ÌŠi”[
	int startTime;
	int itTimeUpImage;
	bool timeUpFlag;
	
	// ¶³ÝÄÀÞ³Ý‚Ì‰æ‘œŠi”[
	int countDownImage[4];
	bool countDownFlag;
	int countDown;
};


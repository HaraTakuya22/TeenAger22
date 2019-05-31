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
	int Init(void);
	// object's list
	Shared_ObjListptr objlist;



	void Draw(void);

	// �ްѼ�݂ɓ�����������ϰ�̊i�[
	int startTime;
	int itTimeUpImage;
	bool timeUpFlag;

	// �����޳݂̉摜�i�[
	int countDownImage[4];
	bool countDownFlag;
	int countDown;

};


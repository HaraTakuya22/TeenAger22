#pragma once
#include "Obj.h"
#include "BaseScene.h"
#include "AddList.h"
class ResultScene:
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	virtual unique_Base Update(unique_Base own, const Controller& controll);
private:
	virtual int Init(void);

	void Draw(void);

	int timeUpImage;
};


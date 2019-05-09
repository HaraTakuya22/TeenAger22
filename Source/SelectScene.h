#pragma once
#include "BaseScene.h"
#include "AddList.h"

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();

	virtual unique_Base Update(unique_Base own, const Controller& Controller);

private:
	virtual int Init(void);
	void Draw(void);

};


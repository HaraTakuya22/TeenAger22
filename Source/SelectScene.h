#pragma once
#include "BaseScene.h"
#include "AddList.h"
#include "Obj.h"

enum button
{
	BUTTON_OFF,
	BUTTON_ON,
	BUTTON_MAX
};
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

	int button1[BUTTON_MAX];
	int button2[BUTTON_MAX];
	int button3[BUTTON_MAX];
	VECTOR2 one_pos;
	VECTOR2 two_pos;
	VECTOR2 three_pos;

	VECTOR2 cursorPos;

	// 表示するマップ
	int titleMapImage;

};


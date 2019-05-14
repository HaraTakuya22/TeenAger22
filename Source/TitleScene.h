#pragma once
#include "BaseScene.h"
#include "AddList.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller);


private:
	// initialize
	virtual int Init(void);
	// object's list
	Shared_ObjListptr objlist;
	void Draw(void);

	// 表示するマップ
	int titleMapImage;
	// 表示するマップのpos
	VECTOR2 titleLeftPos;
	VECTOR2 titleRightPos;
	// 表示してるマップの移動速度
	int moveSpeed;

	// PUSH START BUTTON
	int startButtonImage;
	// startButtonの描画位置
	VECTOR2 startPos1;
	VECTOR2 startPos2;
	VECTOR2 startPos3;
	VECTOR2 startPos4;
	int buttonLeftX;
	int buttonLeftY;
	int buttonRightX;
	int buttonRightY;
	int startButtonCnt;

	// Title画像の格納領域
	int titleImage;

};
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

	// �\������}�b�v
	int titleMapImage;
	// �\������}�b�v��pos
	VECTOR2 titleLeftPos;
	VECTOR2 titleRightPos;
	// �\�����Ă�}�b�v�̈ړ����x
	int moveSpeed;

	// PUSH START BUTTON
	int startButtonImage;
};
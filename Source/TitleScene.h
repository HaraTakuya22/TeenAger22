#pragma once
#include "BaseScene.h"
#include "AddList.h"

#define VIRUS_MAX 10

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
	// startButton�̕`��ʒu
	VECTOR2 startPos1;
	VECTOR2 startPos2;
	VECTOR2 startPos3;
	VECTOR2 startPos4;
	int buttonLeftX;
	int buttonLeftY;
	int buttonRightX;
	int buttonRightY;
	int startButtonCnt;

	// Title�摜�̊i�[�̈�
	int titleImage;

	// ��ٽ�摜�̊i�[�̈�
	int virusImage[200];
	int virusRandImage[200];
	int virusCount;
	int virusRandCount[VIRUS_MAX];

	VECTOR2 virusRandPos[VIRUS_MAX];

};
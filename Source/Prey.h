#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"
#include "Camera.h"

// �S����Ȃ����̻���(Prey = �ǂ������)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ��ڲ԰�̽�߰��
#define SPEED			GRIDSIZE

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos,TYPE_NUM pNum,PLAYER num,VECTOR2 camera);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ��ڲ԰�̕`��
	void Draw(void);
	// ���߂̎󂯎��
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	// ��א����̍ۂ̷�ׂ����߂̎擾
	TYPE_NUM GetTypeNum(void) 
	{
		return typeObjNum;
	}
	// 1P 2P 3P �̏��擾
	PLAYER& GetPlayerNum(void)
	{
		return player;
	}
	// individualsMapPos�̎擾
	/*VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}*/

private:
	bool Init(TYPE_NUM p_num);

	// �e��ׂ̱�Ұ��݂̏�����
	bool AnimInit(void);
};


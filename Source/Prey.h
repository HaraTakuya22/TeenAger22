#pragma once
#include <array>
#include "Map.h"
#include "Obj.h"

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
	Prey(VECTOR2 pos,TYPE_NUM pNum);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ��ڲ԰�̕`��
	void Draw(void);
	// ���߂̎󂯎��
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}
	// typeNum(�����ݲݽ�ݽ����Ă�����ڲ԰��1p�Ȃ̂�)�̎擾
	TYPE_NUM& GetTypeNum(void)
	{
		return typeNum;
	}
	// mapPos�̎擾
	VECTOR2& GetMapPos(void)
	{
		return mapPos;
	}
	// individualsMapPos�̎擾
	VECTOR2& GetIndividualsMapPos(void)
	{
		return individualsMapPos;
	}

private:
	bool Init(TYPE_NUM p_num);
};


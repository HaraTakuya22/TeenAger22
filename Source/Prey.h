#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>

// �S����Ȃ����̻���(Prey = �ǂ������)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ��ڲ԰�̽�߰��
#define SPEED			GRIDSIZE
// ��Ұ��ݺϐ�
#define ANIMATION_MAX	4

typedef struct {
	int		image[DIR_MAX][ANIMATION_MAX];	// ��ڲ԰�摜ID
	bool	Flag;							// ��ڲ԰�̏��
	int		animation;						// ��Ұ���
}CHARACTER;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2* pos, TYPE_NUM p_num);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	// ��ڲ԰�̕`��
	void Draw(void);
	// ���߂̎󂯎��
	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(TYPE_NUM pNum);

	CHARACTER player[PLAYER_MAX];
	int animID[PREY_MAX];
};


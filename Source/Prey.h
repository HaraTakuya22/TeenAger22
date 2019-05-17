#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>

// �S����Ȃ����̻���(Prey = �ǂ������)
#define PREYSIZE_X		GRIDSIZE
#define PREYSIZE_Y		GRIDSIZE * 1.5
// ��ڲ԰�̽�߰��
#define SPEED			GRIDSIZE
// ��ڲ԰��
#define PLAYER_MAX		3
// ��Ұ��ݺϐ�
#define ANIMATION_MAX	4

typedef struct {
	int		image[DIR_MAX][ANIMATION_MAX];	// ��ڲ԰�摜ID
	VECTOR2 pos[PREY_MAX];					// ��ڲ԰���W
	bool	Flag;							// ��ڲ԰�̏��
	int		animation;						// ��Ұ���
	DIR		dir;							// ��ڲ԰�̕���
}CHARACTER;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos, PREY_NUM p_num);
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
	bool Init(PREY_NUM p_num);

	CHARACTER charimage[PREY_MAX];
	CHARACTER player[PLAYER_MAX];

};


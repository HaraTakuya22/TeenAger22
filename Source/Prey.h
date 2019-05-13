#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>


// �S����Ȃ����̻���(Prey = �ǂ������)
#define PREYSIZE_X GRIDSIZE
#define PREYSIZE_Y GRIDSIZE * 1.5


// ��ڲ԰�̽�߰��
#define SPEED	GRIDSIZE

enum TBL_ID {
	TBL_MAIN,
	TBL_SUB,
	TBL_MAX,
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,
	DIR_TBL_OPP,
	DIR_TBL_SUB1,
	DIR_TBL_SUB2,
	DIR_TBL_MAX,
};

enum  SIDE_CHECK {
	OUT_SIDE,
	IN_SIDE,
	SIDE_MAX
};

#define PLAYER_DEF_SPEED 2

// �S����Ȃ����̻���(Prey = �ǂ������)
#define PREYSIZE_X GRIDSIZE
#define PREYSIZE_Y GRIDSIZE * 1.5


using DIR_TBL_ARRAY = std::array<int, DIR_MAX >;
using DIR_TBL_PTR_ARRAY = std::array<int*[TBL_MAX],
	DIR_MAX>;		// ���ڃ|�C���^�ɏ�������ł�
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX],
	DIR_MAX>;
using PASSAGE_TBL = std::array<bool, static_cast<int>(PASSAGE::PASSAGE_MAX)>;

class Prey :
	public Obj
{
public:
	Prey();
	Prey(VECTOR2 pos);
	~Prey();
	void Move(const Controller& controll, WeakList objlist);
	void Draw(void);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_PREY);
	}

private:
	bool Init(void);
	bool afterKeyFlag;				// �������p�׸�

	
	DIR_TBL_ARRAY keyIdTbl;
	DIR_TBL_ARRAY speedTbl;
	DIR_TBL_PTR_ARRAY posTbl;
	DIR_TBL_DIR dirTbl;
	PASSAGE_TBL PassageTbl;		// �A�^������

	VECTOR2 camera;
};


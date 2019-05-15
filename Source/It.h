#pragma once
#include "Map.h"
#include "Obj.h"
#include <array>

// 鬼側のｻｲｽﾞ(It = 追うもの)
#define ITSIZE_X GRIDSIZE
#define ITSIZE_Y GRIDSIZE * 1.5

// 鬼のｽﾋﾟｰﾄﾞ
#define SPEED	GRIDSIZE

enum IT_TBL_ID {
	IT_TBL_MAIN,
	IT_TBL_SUB,
	IT_TBL_MAX,
};

enum IT_DIR_TBL_ID {
	IT_DIR_TBL_MAIN,
	IT_DIR_TBL_OPP,
	IT_DIR_TBL_SUB1,
	IT_DIR_TBL_SUB2,
	IT_DIR_TBL_MAX,
};

enum  IT_SIDE_CHECK {
	IT_OUT_SIDE,
	IT_IN_SIDE,
	IT_SIDE_MAX
};

#define IT_DEF_SPEED 2


using DIR_TBL_ARRAY = std::array<int, DIR_MAX >;
using DIR_TBL_PTR_ARRAY = std::array<int*[IT_TBL_MAX],
	DIR_MAX>;		// 直接ポインタに書き込んでる
using DIR_TBL_DIR = std::array<DIR[IT_DIR_TBL_MAX],
	DIR_MAX>;
using PASSAGE_TBL = std::array<bool, static_cast<int>(PASSAGE::PASSAGE_MAX)>;


class It :
	public Obj
{
public:
	It();
	It(VECTOR2 pos);
	~It();
	void Draw(void);
	void Move(const Controller& controll, WeakList objlist);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_IT);
	}

private:
	bool Init(void);

	bool afterKeyFlag;				// ｷｰ処理用ﾌﾗｸﾞ


	DIR_TBL_ARRAY keyIdTbl;
	DIR_TBL_ARRAY speedTbl;
	DIR_TBL_PTR_ARRAY posTbl;
	DIR_TBL_DIR dirTbl;
	PASSAGE_TBL PassageTbl;		// アタリ判定

	VECTOR2 camera;

};


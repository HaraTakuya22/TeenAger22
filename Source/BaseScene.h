#pragma once
#include <DxLib.h>
#include <memory>
#include "NUM_TYPE.h"
#include "Map.h"
#include "Camera.h"


class Controller;
class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;

// obj�ł��������̂�extern��
// editcursor
extern TYPE_NUM typeCursor;
// 1P�̑I��l��
extern TYPE_NUM typeNum1;
// 2P�̑I��l��
extern TYPE_NUM typeNum2;
// 3P�̑I��l��
extern TYPE_NUM typeNum3;

//// 1P�ȊO���ި���ڲ�ɉf��1P
//extern TYPE_NUM display_typeNum1;
//// 2P�ȊO���ި���ڲ�ɉf��2P
//extern TYPE_NUM display_typeNum2;
//// 3P�ȊO���ި���ڲ�ɉf��3P
//extern TYPE_NUM display_typeNum3;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller) = 0;

private:

	virtual int Init(void) = 0;
};




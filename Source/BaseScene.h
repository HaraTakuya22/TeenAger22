#pragma once
#include <DxLib.h>
#include <memory>
#include "NUM_TYPE.h"
#include "Map.h"


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
// �S�̑I��l��
extern TYPE_NUM typeNumIt;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller) = 0;

private:

	virtual int Init(void) = 0;
};




#pragma once
#include <DxLib.h>
#include <memory>
#include "NUM_TYPE.h"
#include "Map.h"


class Controller;
class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;

// objでも見たいのでexternに
// editcursor
extern TYPE_NUM typeCursor;
// 1Pの選択人物
extern TYPE_NUM typeNum1;
// 2Pの選択人物
extern TYPE_NUM typeNum2;
// 3Pの選択人物
extern TYPE_NUM typeNum3;
// 鬼の選択人物
extern TYPE_NUM typeNumIt;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller) = 0;

private:

	virtual int Init(void) = 0;
};




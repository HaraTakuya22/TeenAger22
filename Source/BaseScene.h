#pragma once
#include <DxLib.h>
#include <memory>
#include "NUM_TYPE.h"
#include "Map.h"
#include "Camera.h"


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

//// 1P以外のﾃﾞｨｽﾌﾟﾚｲに映る1P
//extern TYPE_NUM display_typeNum1;
//// 2P以外のﾃﾞｨｽﾌﾟﾚｲに映る2P
//extern TYPE_NUM display_typeNum2;
//// 3P以外のﾃﾞｨｽﾌﾟﾚｲに映る3P
//extern TYPE_NUM display_typeNum3;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller) = 0;

private:

	virtual int Init(void) = 0;
};




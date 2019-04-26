#pragma once
#include <DxLib.h>
#include <memory>


class Controller;
class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;



class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own, const Controller& Controller) = 0;

private:

	virtual int Init(void) = 0;
};




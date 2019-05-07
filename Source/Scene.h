#pragma once
#include <mutex>
#include <DxLib.h>
#include "BaseScene.h"
#include "Controller.h"
#include "VECTOR2.h"


// ‰æ–Ê»²½Þ
#define SCREENSIZE_X 1200
#define SCREENSIZE_Y 660

#define lpScene	Scene::getInstance()

class Scene
{
public:
	static void Destroy(void);
	static Scene &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *sceneins;
	}
	void onceRun(void);

	VECTOR2 GetScrSize(void)
	{
		return VECTOR2(SCREENSIZE_X, SCREENSIZE_Y);
	}

private:

	Scene();
	~Scene();

	static std::once_flag onceflag;
	static Scene* sceneins;

	static void Create(void);

	bool(Scene::*s_ptr)(void);

	// scene's shift
	unique_Base sceneshift;

	// system initialize
	bool SystemInit(void);

	// instance(static)
	std::unique_ptr<Controller> gamectl;
};

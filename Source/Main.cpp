#include <DxLib.h>
#include "Scene.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Scene::getInstance().onceRun();

	Scene::Destroy();

}
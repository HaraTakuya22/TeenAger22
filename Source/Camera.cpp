#include "Camera.h"
#include "Scene.h"
//#include "Controller.h"


bool Camera::Update(Controller cnt)
{
	auto cnt_now = cnt.GetButtonInfo()[KEY_TYPE_NOW];
	auto cnt_old = cnt.GetButtonInfo()[KEY_TYPE_OLD];
	
	if (cnt_now[CAMERA_LEFT] & ~cnt_old[CAMERA_LEFT])
	{
		cameraPos.x -= cameraSpeed.x;
	}
	if (cnt_now[CAMERA_RIGHT] & ~cnt_old[CAMERA_RIGHT])
	{
		cameraPos.x += cameraSpeed.x;
	}
	if (cnt_now[CAMERA_DOWN] & ~cnt_old[CAMERA_DOWN])
	{
		cameraPos.y += cameraSpeed.y;
	}
	if (cnt_now[CAMERA_UP] & ~cnt_old[CAMERA_UP])
	{
		cameraPos.y -= cameraSpeed.y;
	}
	
	return true;
}

Camera::Camera(VECTOR2 Ppos,VECTOR2 objCamera,VECTOR2 speed,PLAYER player)
{
	Init();

	cameraPos = Ppos - objCamera;
}


Camera::~Camera()
{
}

bool Camera::Init()
{
	cameraSpeed = { GRIDSIZE,GRIDSIZE };

	return true;
}

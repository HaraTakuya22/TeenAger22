#pragma once


#include "VECTOR2.h"
#include "Map.h"

using namespace std;

class Controller;

#define CAMERA_SPEED GRIDSIZE

class Camera
{
public:
	Camera(VECTOR2 Cpos,VECTOR2 objCamera,VECTOR2 speed,PLAYER player);
	~Camera();

	bool Update(Controller cnt);

	VECTOR2& GetCamera(void)
	{
		return cameraPos;
	}
private:
	
	bool Init();


	VECTOR2 cameraPos;
	VECTOR2 cameraSpeed;
};


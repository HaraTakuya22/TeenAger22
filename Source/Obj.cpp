#include <DxLib.h>

#include "Obj.h"
#include "Image.h"


Obj::Obj()
{
	deleteflag = false;
	
	pos[typeNum] = player_cameraPos[typeNum];
}


Obj::~Obj()
{
}

void Obj::Draw(void)
{
	if (ImageName.length() == 0)
	{
		return;
	}
	int ID = 0;

	AniCnt[typeNum]++;
	if (animTbl.find(AnimationName) != animTbl.end())
	{
		int start = animTbl[AnimationName][ANIM_START];
		int inter = (AniCnt[typeNum] / animTbl[AnimationName][ANIM_INTERVAL]);
		int flame = animTbl[AnimationName][ANIM_FLAME];
		ID = start + (int)dir + (inter % flame) * DivCnt.x;
	}

	DrawGraph(pos[typeNum].x + player_cameraPos[typeNum].x - pos[typeNum].x, pos[typeNum].y + player_cameraPos[typeNum].y - pos[typeNum].y, ImageID(ImageName)[ID], true);
}

void Obj::Draw(unsigned int id)
{
	if (id < ImageID(ImageName).size())
	{
		DrawGraph(pos[typeNum].x, pos[typeNum].y, ImageID(ImageName)[id], true);
	}
}

void Obj::Update(const Controller & controll, WeakList objlist)
{
	Move(controll, objlist);
}

bool Obj::Init(std::string filename, VECTOR2 divcnt, VECTOR2 divsize)
{
	this->DivCnt = divcnt;
	this->DivSize = divsize;
	ImageName = filename;
	lpImage.GetID(filename, divcnt, divsize);
	return true;
}

bool Obj::AddAnim(std::string animationName, int x, int y, int flame, int val)
{
	animTbl[animationName][ANIM_START] = DivCnt.x * y + x;
	animTbl[animationName][ANIM_FLAME] = flame;
	animTbl[animationName][ANIM_INTERVAL] = val;
	return true;
}

bool Obj::SetAnim(std::string animationName)
{
	if (Obj::AnimationName == animationName)
	{
		return true;
	}
	if (animTbl.find(animationName) == animTbl.end())
	{
		return false;
	}
	Obj::AnimationName = animationName;
	Obj::AniCnt[typeNum] = 0;
	return true;
}

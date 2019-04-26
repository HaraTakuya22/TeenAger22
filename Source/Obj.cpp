#include <DxLib.h>
#include "Obj.h"
#include "Image.h"


Obj::Obj()
{
	deleteflag = false;

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

	AniCnt++;
	if (animTbl.find(AnimationName) != animTbl.end())
	{
		int start = animTbl[AnimationName][ANIM_START];
		int inter = (AniCnt / animTbl[AnimationName][ANIM_INTERVAL]);
		int flame = animTbl[AnimationName][ANIM_FLAME];
		ID = start + (inter % flame) * DivCnt.x;
	}
	DrawGraph(pos.x, pos.y, ImageID(ImageName)[ID], true);
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
	Obj::AniCnt = 0;
	return true;
}

#include <DxLib.h>

#include "Scene.h"
#include "SelectScene.h"
#include "Obj.h"
#include "Image.h"

Obj::Obj()
{
	//dir = DIR_DOWN;
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

	if (animTbl.find(AnimationName) != animTbl.end())
	{
		int start = animTbl[AnimationName][ANIM_START];
		int inter = (AniCnt / animTbl[AnimationName][ANIM_INTERVAL]);
		int flame = animTbl[AnimationName][ANIM_FLAME];
		ID = (start + dir * DivCnt.y) + (AniCnt);
	}
	
	// playerCnt:1P 2P or 3P(Ãﬂ⁄≤‘∞êîÇ…âûÇ∂Çƒï`âÊÇ∑ÇÈà íuÇïœâª)
	DrawGraph(fixedPos.x + ((lpScene.GetScrSize().x / 2) * ((int)player - 1)), fixedPos.y, ImageID(ImageName)[ID], true);

	//lpMap.OtherPreyDraw(ImageID(ImageName)[ID],individualsMapPos,playerCnt);
}

void Obj::Draw(unsigned int id)
{
	if (id < ImageID(ImageName).size())
	{
		DrawGraph(pos.x, pos.y, ImageID(ImageName)[id], true);
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

bool Obj::AddAnim(std::string animationName,int flame, int val)
{
	animTbl[animationName][ANIM_START] = DivCnt.y * dir;
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

#pragma once
#include<DxLib.h>
#include <mutex>
#include <vector>
#include <map>

#include "VECTOR2.h"



//¼Ý¸ÞÙÄÝ---------------------------------------------
#define ImageID(X) (Image::getInstance().GetID(X))
#define lpImage Image::getInstance()
//----------------------------------------------------
using VecInt = std::vector<int>;

class Image
{
public:
	static void destroy(void);

	static Image &getInstance(void)
	{
		std::call_once(Flag, create);
		return *ImageInstance;
	}
	const VecInt& GetID(std::string filename, VECTOR2 divcnt, VECTOR2 divsize);
	const VecInt& GetID(std::string filename);
private:
	Image();
	~Image();

	static void create(void);
	static Image *ImageInstance;
	static std::once_flag Flag;
	//‰æ‘œ‚ð"·°"‚Å”»•Ê‚³‚¹‚é
	std::map <std::string, VecInt> ImageMap;
};


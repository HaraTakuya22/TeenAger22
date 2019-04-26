#include "Image.h"


//nullptr = ｱﾄﾞﾚｽなし
Image* Image::ImageInstance = nullptr;
//call_onceを呼び出すためのﾌﾗｸﾞ
std::once_flag Image::Flag;


Image::Image()
{
}


Image::~Image()
{
}

//一回作ったらすぐに消す
void Image::destroy(void)
{
	if (ImageInstance != nullptr)
	{
		delete ImageInstance;
	}
	//再度中身を空にする
	ImageInstance = nullptr;
}

//画像の名前取得（引数1:画像の名前、引数2:画像分割数、引数3:画像分割ｻｲｽﾞ）＜分割して画像を表示する場合＞
const VecInt & Image::GetID(std::string filename, VECTOR2 divcnt, VECTOR2 divsize)
{
	if (ImageMap.find(filename) == ImageMap.end())
	{
		ImageMap[filename].resize(divcnt.x * divcnt.y);
		LoadDivGraph(filename.c_str(), divcnt.x * divcnt.y, divcnt.x, divcnt.y, divsize.x, divsize.y, &ImageMap[filename][0], true);
	}
	return ImageMap[filename];
}

//単なる画像の名前の取得
const VecInt & Image::GetID(std::string filename)
{
	if (ImageMap.find(filename) == ImageMap.end())
	{
		ImageMap[filename].resize(1);
		ImageMap[filename][0] = LoadGraph(filename.c_str());
	}
	return ImageMap[filename];
}

//Imageのｲﾝｽﾀﾝｽ
void Image::create(void)
{
	ImageInstance = new Image();
}

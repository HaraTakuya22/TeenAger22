#include "Image.h"


//nullptr = ���ڽ�Ȃ�
Image* Image::ImageInstance = nullptr;
//call_once���Ăяo�����߂��׸�
std::once_flag Image::Flag;


Image::Image()
{
}


Image::~Image()
{
}

//��������炷���ɏ���
void Image::destroy(void)
{
	if (ImageInstance != nullptr)
	{
		delete ImageInstance;
	}
	//�ēx���g����ɂ���
	ImageInstance = nullptr;
}

//�摜�̖��O�擾�i����1:�摜�̖��O�A����2:�摜�������A����3:�摜�������ށj���������ĉ摜��\������ꍇ��
const VecInt & Image::GetID(std::string filename, VECTOR2 divcnt, VECTOR2 divsize)
{
	if (ImageMap.find(filename) == ImageMap.end())
	{
		ImageMap[filename].resize(divcnt.x * divcnt.y);
		LoadDivGraph(filename.c_str(), divcnt.x * divcnt.y, divcnt.x, divcnt.y, divsize.x, divsize.y, &ImageMap[filename][0], true);
	}
	return ImageMap[filename];
}

//�P�Ȃ�摜�̖��O�̎擾
const VecInt & Image::GetID(std::string filename)
{
	if (ImageMap.find(filename) == ImageMap.end())
	{
		ImageMap[filename].resize(1);
		ImageMap[filename][0] = LoadGraph(filename.c_str());
	}
	return ImageMap[filename];
}

//Image�̲ݽ�ݽ
void Image::create(void)
{
	ImageInstance = new Image();
}

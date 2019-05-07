#include "Scene.h"
#include "TitleScene.h"


Scene* Scene::sceneins = nullptr;
std::once_flag Scene::onceflag;

void Scene::onceRun(void)
{
	sceneshift = std::make_unique<TitleScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���X�N���[���̐؂�ւ����s���B
		if (CheckHitKey(KEY_INPUT_F1) && !isFullScreen)
		{
			ChangeWindowMode(FALSE);
			SetDrawScreen(DX_SCREEN_BACK);
			isFullScreen = true;
		}
		if (CheckHitKey(KEY_INPUT_F2) && isFullScreen)
		{
			ChangeWindowMode(TRUE);
			SetDrawScreen(DX_SCREEN_BACK);
			isFullScreen = false;
		}
		sceneshift = sceneshift->Update(std::move(sceneshift), (*gamectl));
		gamectl->Update();
	}

	

}

Scene::Scene()
{
	SystemInit();
}


Scene::~Scene()
{

}

void Scene::Create(void)
{
	sceneins = new Scene();
}

void Scene::Destroy(void)
{
	if (sceneins != nullptr)
	{
		delete sceneins;
	}
	sceneins = nullptr;
}

bool Scene::SystemInit(void)
{
	isFullScreen = false;

	SetGraphMode(SCREENSIZE_X, SCREENSIZE_Y, 32);		

	ChangeWindowMode(true);								//true:window�@false:�ٽ�ذ�
	SetWindowText("sample");
	if (DxLib_Init() == -1) return false;				//DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);

	gamectl = std::make_unique<Controller>();

	return true;
}
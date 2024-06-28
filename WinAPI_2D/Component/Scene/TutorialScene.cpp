#include "TutorialScene.h"

namespace LJG
{

	TutorialScene::TutorialScene()
		: UScene(L"data/scenes/intro") {}

	TutorialScene::~TutorialScene() = default;

	void TutorialScene::Initialize()
	{
		LoadScene();
	}

	void TutorialScene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);
	}

	void TutorialScene::Render()
	{
		UScene::Render();
	}

	void TutorialScene::Release()
	{
		UScene::Release();
	}
}

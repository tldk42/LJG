#include "UScene.h"

#include "Component/UImage.h"
#include "Component/Manager/ObjectManager.h"
#include "Component/UObject.h"
#include "Component/Actor/AAnimatedImage.h"
#include "Component/Manager/SoundManager.h"
#include "Game/Animator/TitleScreenAnimator.h"
#include "GUI/GUI_MapEditor.h"
#include "Helper/EngineHelper.h"
#include "Shape/CollisionManager.h"

namespace LJG
{

	UScene::UScene(const WText& InKey)
		: UObject(InKey)
	{
		// mSavedData = EngineHelper::LoadFile(InKey);
	}

	UScene::~UScene() {}

	void UScene::Initialize()
	{
		UObject::Initialize();
		Manager_Collision.Initialize();
	}

	void UScene::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);
		Manager_Object.Update(DeltaTime);
		Manager_Collision.Update(DeltaTime);
	}

	void UScene::Render()
	{
		UObject::Render();
		Manager_Object.Render();
		Manager_Collision.Render();
	}

	void UScene::Release()
	{
		UObject::Release();
		// Manager_Collision.Release();
		Manager_Object.Release();
		Manager_Audio.StopAll();
	}

	void UScene::LoadScene()
	{
		// if (mSavedData != nullptr)
		// {
		// 	for (const auto& element : mSavedData)
		// 	{
		// 		FMapData savedData;
		// 		savedData = element.get<FMapData>();
		// 		if (const size_t pos = savedData.Key.find('_'); pos != Text::npos)
		// 		{
		// 			Text type = savedData.Key.substr(0, pos);
		// 			// if (type == "Anim")
		// 			// {
		// 			// 	AAnimatedImage* animatedImage = Manager_Object.CreateOrLoad<AAnimatedImage>(
		// 			// 		Text2WText(savedData.Key));
		// 			// 	animatedImage->SetAnimator(Manager_Object.CreateOrLoad<TitleScreenAnimator>(L""));
		// 			// 	animatedImage->SetScale(savedData.Scale);
		// 			// 	animatedImage->SetWorldLocation(savedData.Position);
		// 			// }
		//
		// 		}
		// 		else
		// 		{
		// 			UImage* image = Manager_Object.CreateOrLoad<UImage>(Text2WText(savedData.Key), savedData.TexPath,
		// 																savedData.ZOrder);
		// 			image->SetScale(savedData.Scale);
		// 			image->SetPosition(savedData.Position);
		// 		}
		// 	}
		// 	return;
		// }
		//
		// // TODO: 파일 매니저에서 씬 경로 \\ 키값이름.json 확인
		// nlohmann::json jsonData = EngineHelper::LoadFile(mSceneFile);
		//
		// if (jsonData == nullptr)
		// 	return;
		//
		// for (const auto& element : jsonData)
		// {
		// 	FMapData savedData;
		// 	savedData     = element.get<FMapData>();
		// 	UImage* image = Manager_Object.CreateOrLoad<UImage>(Text2WText(savedData.Key), savedData.TexPath,
		// 														savedData.ZOrder);
		// 	image->SetPosition(savedData.Position);
		// }
	}

	void UScene::MoveScene(WTextView InNextScene) {}

	void UScene::EndScene()
	{
		Release();
	}
}

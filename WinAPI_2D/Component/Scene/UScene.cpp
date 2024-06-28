#include "UScene.h"

#include "Component/UImage.h"
#include "Component/Manager/ObjectManager.h"
#include "Component/UObject.h"
#include "GUI/GUI_MapEditor.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	UScene::UScene(const WText& InKey)
		: mSceneFile(InKey)
	{
		mSavedData = EngineHelper::LoadFile(mSceneFile);
	}

	UScene::~UScene() {}

	void UScene::Initialize()
	{}

	void UScene::Update(float DeltaTime)
	{
		// Manager_Object.Update(DeltaTime);
	}

	void UScene::Render()
	{
		// Manager_Object.Render();
	}

	void UScene::Release()
	{}

	void UScene::LoadScene()
	{
		if (mSavedData != nullptr)
		{
			for (const auto& element : mSavedData)
			{
				FMapData savedData;
				savedData     = element.get<FMapData>();
				UImage* image = Manager_Object.CreateOrLoad<UImage>(Text2WText(savedData.Key), savedData.TexPath,
																	savedData.ZOrder);
				image->SetScale(savedData.Scale);
				image->SetPosition(savedData.Position);
			}
			return;
		}

		// TODO: ���� �Ŵ������� �� ��� \\ Ű���̸�.json Ȯ��
		nlohmann::json jsonData = EngineHelper::LoadFile(mSceneFile);

		if (jsonData == nullptr)
			return;

		for (const auto& element : jsonData)
		{
			FMapData savedData;
			savedData     = element.get<FMapData>();
			UImage* image = Manager_Object.CreateOrLoad<UImage>(Text2WText(savedData.Key), savedData.TexPath,
																savedData.ZOrder);
			image->SetPosition(savedData.Position);
		}
	}

	void UScene::EndScene()
	{
		Manager_Object.Release();
	}
}

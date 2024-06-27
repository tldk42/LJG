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
	{}

	UScene::~UScene() {}

	void UScene::Initialize()
	{
		Manager_Object.Initialize();
	}

	void UScene::Update(float DeltaTime)
	{
		Manager_Object.Update(DeltaTime);
	}

	void UScene::Render()
	{
		Manager_Object.Render();
	}

	void UScene::Release()
	{
		Manager_Object.Release();
	}

	void UScene::LoadScene()
	{
		// TODO: 파일 매니저에서 씬 경로 \\ 키값이름.json 확인
		nlohmann::json jsonData = EngineHelper::LoadFile(mSceneFile);

		if (!jsonData)
			return;

		std::vector<FMapData> mapDataVec;
		// for (const auto& element : jsonData)
		// {
		// 	FMapData savedData;
		// 	savedData     = element.get<FMapData>();
		// 	UImage* image = Manager_Object.CreateOrLoad<UImage>(Text2WText(savedData.Key), savedData.TexPath);
		// 	image->SetPosition(savedData.Position);
		// 	// mapDataVec.push_back(savedData);
		// }
	}

	void UScene::EndScene() {}
}

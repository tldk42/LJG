#include "UObject.h"

#include "DirectX/XSprite2D.h"
#include "Helper/EngineHelper.h"


namespace LJG
{
	UObject::UObject()
	{
		static uint32_t objectNum = 0;
		mObjectKey                = std::format(L"{}_{}", Text2WText(__func__), objectNum++);
	}

	UObject::UObject(const WText& InKey)
		: mObjectKey(InKey),
		  mOwnerActor(nullptr) {}

	UObject::UObject(AActor* InOwnerActor)
		: mOwnerActor(InOwnerActor) {}

	UObject::~UObject()
	{
		UObject::Release();
	}

	void UObject::Initialize() {}

	void UObject::Update(float DeltaTime)
	{
		for (const auto& object : mChildObjects)
		{
			object.second->Update(DeltaTime);
		}
	}

	void UObject::Render() {}
	void UObject::Release() {}

	void UObject::Destroy(const WText& InKey)
	{
		if (mChildObjects.contains(InKey))
		{
			mChildObjects.erase(InKey);
		}
	}

	void UObject::AttachComponent(UObject* ComponentToAttach)
	{
		ComponentToAttach->SetupAttachment(this);
	}

	void UObject::SetupAttachment(UObject* InParentObj)
	{
		InParentObj->mChildObjects.try_emplace(mObjectKey, this);
	}


}

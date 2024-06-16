#include "UObject.h"

#include "DirectX/XSprite2D.h"


namespace LJG
{
	UObject::UObject()
		: mOwnerActor(nullptr),
		  mParentObject(nullptr) {}

	UObject::UObject(AActor* InOwnerActor)
		: mOwnerActor(InOwnerActor),
		  mParentObject(nullptr) {}

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

	void UObject::AttachComponent(UObject* ComponentToAttach)
	{
		ComponentToAttach->SetupAttachment(this);
	}

	void UObject::SetupAttachment(UObject* InParentObj)
	{
		InParentObj->mChildObjects.try_emplace(mObjectID, this);

		mParentObject = InParentObj;
	}


}

#include "AActor.h"

#include <memory>

namespace LJG
{
	AActor::AActor(const WText& InKey)
		: USceneComponent(InKey)
	{
		bVisibility = true;
	}


	void AActor::Initialize()
	{
		UObject::Initialize();
	}

	void AActor::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);
	}

	void AActor::Render()
	{
		if (bVisibility)
		{
			for (auto& [key, object] : mChildObjects)
			{
				object->Render();
			}
		}
	}

	void AActor::Release()
	{
		UObject::Release();
	}

	void AActor::AttachComponent(const WText& InCompID, UObject* InComp)
	{
		if (!mChildObjects.contains(InCompID))
		{
			// mChildObjects[InCompID] = InComp;
			mChildObjects[InCompID]->SetOwnerActor(this);
		}
	}

	UObject* AActor::GetComponentByID(const WText& InCompID)
	{
		if (mChildObjects.contains(InCompID))
		{
			return mChildObjects[InCompID].get();
		}
		return nullptr;
	}
}

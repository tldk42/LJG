#include "AActor.h"

#include <memory>

namespace LJG
{
	AActor::AActor()
		: mLocation(FVector2f::ZeroVector),
		  mScale(FVector2f::UnitVector) {}

	AActor::~AActor() {}

	void AActor::Initialize()
	{
		UObject::Initialize();
	}

	void AActor::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		for (const auto& component : mChildComponents)
		{
			component.second->Update(DeltaTime);
		}
	}

	void AActor::Render()
	{
		UObject::Render();

		for (const auto& component : mChildComponents)
		{
			component.second->Render();
		}
	}

	void AActor::Release()
	{
		UObject::Release();
	}

	void AActor::AttachComponent(const std::wstring& InCompID, const UObjectSPtr& InComp)
	{
		if (!mChildComponents.contains(InCompID))
		{
			mChildComponents[InCompID] = InComp;
			mChildComponents[InCompID]->SetOwnerActor(this);
		}
	}

	UObjectSPtr AActor::GetComponentByID(const std::wstring& InCompID)
	{
		if (!mChildComponents.contains(InCompID))
		{
			return mChildComponents[InCompID];
		}
		return nullptr;
	}
}

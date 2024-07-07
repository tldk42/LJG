#include "AInteractObject.h"

#include "Shape/UBoxComponent.h"

namespace LJG
{

	AInteractObject::AInteractObject(const WText& InKey)
		: AActor(InKey)
	{
		mBoxComponent = CreateDefaultSubObject<UBoxComponent>(L"InteractableBox", ETraceType::Interact);
	}

	AInteractObject::~AInteractObject() {}

	void AInteractObject::Initialize()
	{
		AActor::Initialize();
	}

	void AInteractObject::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);
	}

	void AInteractObject::Render()
	{
		AActor::Render();
	}

	void AInteractObject::Release()
	{
		AActor::Release();
	}

	void AInteractObject::OnBeginInteract(FHitResult_Box2D& HitResult) {}
	void AInteractObject::OnEndInteract(FHitResult_Box2D& HitResult) {}
}

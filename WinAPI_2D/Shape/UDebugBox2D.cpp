#include "UDebugBox2D.h"

#include "XDebugShape2D.h"
#include "../AActor.h"
#include "../Context.h"

namespace LJG
{
	UDebugBox2D::UDebugBox2D()
	{
		UDebugBox2D::Initialize();
	}

	void UDebugBox2D::Initialize()
	{
		mDebugShape = std::make_unique<XDebugShape2D>();
		mDebugShape->Initialize();
	}

	void UDebugBox2D::Update(float DeltaTime)
	{
		mDebugShape->Update(DeltaTime);
		mDebugShape->SetWorldLocation(mOwnerActor->GetActorLocation());
		mDebugShape->SetWorldRotation(mOwnerActor->GetActorRotation());
	}

	void UDebugBox2D::Render()
	{
		mDebugShape->Render();
	}

	void UDebugBox2D::Release()
	{
		mDebugShape->Release();
	}

	void UDebugBox2D::SetScale(const FVector2f& InScale) const
	{
		mDebugShape->SetScale(InScale);
	}

	void UDebugBox2D::SetColor(const FLinearColor& InColor) const
	{
		mDebugShape->SetColor(InColor);
	}
}

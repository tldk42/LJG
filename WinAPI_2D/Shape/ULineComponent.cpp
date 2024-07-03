#include "ULineComponent.h"

#include "CollisionManager.h"
#include "XShape2D_Line.h"
#include "Component/Actor/AActor.h"

LJG::ULineComponent::ULineComponent(const WText& Inkey)
	: USceneComponent(Inkey)
{
	// LineTypes.AddComponent(ETraceType::Ground, this);

	ULineComponent::Initialize();
}

LJG::ULineComponent::~ULineComponent()
{
	// LineTypes.RemoveComponent(this);
}

void LJG::ULineComponent::Initialize()
{
	mLineShape = std::make_unique<XShape2D_Line>();
	mLineShape->Initialize();
}

void LJG::ULineComponent::Update(float DeltaTime)
{
	mLineShape->Update(DeltaTime);
	// if (!OnComponentBeginOverlap.functions.empty())
	// {
	// 	FHitResult hitResult;
	// 	if (LineTrace2Box(mLine.Origin, mLine.Target, ETraceType::Ground, hitResult))
	// 	{
	// 		OnComponentBeginOverlap.Execute(mLine.Origin, mLine.Target, hitResult);
	// 	}
	// }

	if (mOwnerActor)
	{
		mLineShape->SetWorldLocation(mOwnerActor->GetWorldLocation() - FVector2f(0, 76.f));
		const auto cache = mLineShape->GetLocation() - mLine.Origin;
		mLine.Origin     = mLineShape->GetLocation();
		mLine.Target += cache;
	}
}

void LJG::ULineComponent::Render()
{
	mLineShape->Render();
}

void LJG::ULineComponent::Release()
{
	mLineShape->Release();

}

void LJG::ULineComponent::SetScale(const FVector2f& InScale)
{
	USceneComponent::SetScale(InScale);
	mLineShape->SetScale(InScale);
	mLine.Target *= InScale;
}

void LJG::ULineComponent::SetColor(const FLinearColor& InColor) const
{
	mLineShape->SetColor(InColor);

}

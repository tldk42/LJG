#include "ULineComponent.h"

#include "XShape2D_Line.h"
#include "Component/Actor/AActor.h"

LJG::ULineComponent::ULineComponent(const WText& Inkey)
	: USceneComponent(Inkey)
{
	ULineComponent::Initialize();
}

void LJG::ULineComponent::Initialize()
{
	mLineShape = std::make_unique<XShape2D_Line>();
	mLineShape->Initialize();
}

void LJG::ULineComponent::Update(float DeltaTime)
{
	mLineShape->Update(DeltaTime);

	if (mOwnerActor)
	{
		mLineShape->SetWorldLocation(mOwnerActor->GetWorldLocation());
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
	mLineShape->SetScale(InScale);
}

void LJG::ULineComponent::SetColor(const FLinearColor& InColor) const
{
	mLineShape->SetColor(InColor);

}

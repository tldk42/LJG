#include "ParryCircle.h"

#include "Component/UImage.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Manager/TextureManager.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ParryCircle::ParryCircle(const WText& InKey)
		: AInteractObject(InKey)
	{
		mCircle_Pink = Manager_Texture.CreateOrLoad(L"rsc/Sprite/tutorial_pink_sphere_1.png");
		mCircle_Gray = Manager_Texture.CreateOrLoad(L"rsc/Sprite/tutorial_sphere_1.png");

		mParryCircle = CreateDefaultSubObject<UImage>(InKey);
		mParryCircle->SetTexture(mCircle_Pink);

		mBoxComponent->SetScale({15, 15.f});
		mBoxComponent->OnCollisionEnter_Delegate.Bind(
			std::bind(&ParryCircle::OnBeginInteract, this, std::placeholders::_1));
		mBoxComponent->OnCollisionExit_Delegate.Bind(
			std::bind(&ParryCircle::OnEndInteract, this, std::placeholders::_1));
	}

	ParryCircle::~ParryCircle() {}

	void ParryCircle::Initialize()
	{
		AInteractObject::Initialize();
	}

	void ParryCircle::Update(float DeltaTime)
	{
		AInteractObject::Update(DeltaTime);

		if (!bCanBeParry)
		{
			mElapsedTime += DeltaTime;
			if (mElapsedTime > 3.f)
			{
				mElapsedTime = 0.f;
				bCanBeParry  = true;
				mParryCircle->SetTexture(mCircle_Pink);
			}
		}
	}

	void ParryCircle::Render()
	{
		AInteractObject::Render();
	}

	void ParryCircle::Release()
	{
		AInteractObject::Release();
	}

	void ParryCircle::OnBeginInteract(FHitResult_Box2D& HitResult)
	{
		if (HitResult.Src->GetTraceType() == ETraceType::Pawn)
		{
			if (bCanBeParry && LocalPlayer.IsParring())
			{
				LocalPlayer.HandleParry();
				bCanBeParry = false;
				mParryCircle->SetTexture(mCircle_Gray);
			}
		}
	}

	void ParryCircle::OnEndInteract(FHitResult_Box2D& HitResult)
	{
		if (HitResult.Src->GetTraceType() == ETraceType::Pawn)
		{
			// bCanBeParry = false;
		}
	}

	void ParryCircle::SetWorldLocation(const FVector2f& InLocation)
	{
		AInteractObject::SetWorldLocation(InLocation);

		mParryCircle->SetWorldLocation(InLocation);
		mBoxComponent->SetWorldLocation(InLocation);
	}

	void ParryCircle::SetScale(const FVector2f& InScale)
	{
		AInteractObject::SetScale(InScale);

		mParryCircle->SetScale(InScale);
		mBoxComponent->SetScale(InScale);
	}
}

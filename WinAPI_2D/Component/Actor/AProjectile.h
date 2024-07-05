#pragma once
#include "AActor.h"
#include "FTimer.h"

namespace LJG
{
	class USpriteAnimation;


	/**
	 * \brief 발사체 Base
	 * 이미지나 충돌체를 변경하려면 Base의 Initialize호출 이후
	 * mBoxComponent->SetScale
	 * mAnim->SetAnimData
	 */
	class AProjectile : public AActor
	{
	public:
		AProjectile();
		explicit AProjectile(const struct FAnimData& InAnimData, const FVector2f& InSize = FVector2f::UnitVector,
							 const FVector2f&        InVelocity                          = FVector2f(1000.f));
		~AProjectile() override;

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void AddWorldLocation(const FVector2f& InAddLocation) override;
		void SetWorldLocation(const FVector2f& InLocation) override;
		void SetWorldRotation(const float InDegree) override;
		void Launch();

	public:
		void SetLifeTime(const float_t InLifeTime);
		void SetDamage(const float_t InDamage);
		void SetVelocity(const FVector2f& InVelocity);
		void SetCollisionBoxSize(const FVector2f& InSize) const;
		void SetAnimation(const struct FAnimData& InAnimData) const;

	protected:
		virtual void OnCollisionEnter(FHitResult_Box2D& HitResult);

	protected:
		//======================== Data ==========================
		bool      bLaunched;
		float_t   mLifeTime;
		float_t   mDamage;
		FVector2f mVelocity;
		FVector2f mBoxSize;

		//====================== Resource =========================
		XSprite2DUPtr     mSprite2D;
		USpriteAnimation* mAnim;
		UBoxComponent*    mBoxComponent; // Default Size 80,40

		FTimer timer;

	private:
		static int32_t mObjectNum;
	};
}

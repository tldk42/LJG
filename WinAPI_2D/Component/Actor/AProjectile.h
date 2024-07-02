#pragma once
#include "AActor.h"

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
		~AProjectile() override;

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetWorldLocation(const FVector2f& InLocation) override;
		void Launch();

	protected:
		//======================== Data ==========================
		bool      bLaunched;
		float_t   mLifeTime;
		FVector2f mVelocity;

		//====================== Resource =========================
		XSprite2DUPtr     mSprite2D;
		USpriteAnimation* mAnim;
		UBoxComponent*    mBoxComponent; // Default Size 80,40

	private:
		static int32_t mObjectNum;
	};
}

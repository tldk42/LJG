#pragma once
#include "AActor.h"
namespace LJG
{
	class UPlayerAnimator;
}
namespace LJG
{
	class UDebugBox2D;
}
namespace LJG
{
	class APlayerController : public AActor
	{
	public:
		APlayerController();
		~APlayerController() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void AddMovementInput(const FVector2f& MovementInputAmount);

	private:
		UPlayerAnimator*             mAnimator;
		std::unique_ptr<UDebugBox2D> mDebugBox;
	};
}

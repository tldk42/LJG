#pragma once
#include "Component/Actor/AActor.h"

namespace LJG
{
	class UImage;

	class Ground : public AActor
	{
	public:
		Ground(const WText& InText);
		~Ground() override;

		// 	public:
		// #pragma region Core Interface
				void Initialize() override;
		// 		void Update(float DeltaTime) override;
		// 		void Render() override;
		// 		void Release() override;
		// #pragma endregion

	public:
		void SetTexture(WTextView InKey, WTextView InPath);
		void SetBoxSize(const FVector2f& InSize) const;
		void SetWorldLocation(const FVector2f& InLocation) override;
		void SetScale(const FVector2f& InScale) override;

	protected:
		UImage*        mImage;
		UBoxComponent* mBoxComponent;
	};
}

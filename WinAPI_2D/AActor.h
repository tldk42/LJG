#pragma once
#include "UObject.h"

namespace LJG
{
	class AActor : public UObject
	{
	public:
		AActor();
		~AActor() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		[[nodiscard]] inline FVector2f GetActorLocation() const { return mLocation; }
		[[nodiscard]] inline FVector2f GetActorScale() const { return mScale; }
		[[nodiscard]] UObject*         GetComponentByID(const WText& InCompID);


		inline void SetActorLocation(const FVector2f& InLocation) { mLocation = InLocation; }
		inline void SetActorScale(const FVector2f& InScale) { mScale = InScale; }
		void        AttachComponent(const WText& InCompID, UObject* InComp);

	protected:
		bool bVisibility;

		FVector2f mLocation;
		FVector2f mScale;
	};
}

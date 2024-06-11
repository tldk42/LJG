#pragma once
#include "UObject.h"

namespace LJG
{
	class AActor : public UObject
	{
	public:
		AActor();
		~AActor() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		[[nodiscard]] inline FVector2f GetActorLocation() const { return mLocation; }
		[[nodiscard]] inline FVector2f GetActorScale() const { return mScale; }
		[[nodiscard]] UObjectSPtr      GetComponentByID(const std::wstring& InCompID);


		inline void SetActorLocation(const FVector2f& InLocation) { mLocation = InLocation; }
		inline void SetActorScale(const FVector2f& InScale) { mScale = InScale; }
		void        AttachComponent(const std::wstring& InCompID, const UObjectSPtr& InComp);

	protected:
		FVector2f mLocation;
		FVector2f mScale;

		std::unordered_map<std::wstring, UObjectSPtr> mChildComponents;
	};
}

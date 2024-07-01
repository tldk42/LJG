#pragma once
#include "Component/USceneComponent.h"

namespace LJG
{
	class AActor : public USceneComponent
	{
	public:
		explicit AActor(const WText& InKey);
		~AActor() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		[[nodiscard]] UObject* GetComponentByID(const WText& InCompID);

		void AttachComponent(const WText& InCompID, UObject* InComp);

		void HideInGame(bool bHide) { bVisibility = bHide; }

	protected:
	};
}

#pragma once
#include "Component/Actor/AActor.h"

namespace LJG
{

	class AInteractObject : public AActor, public IInteractableAPI
	{
	public:
		AInteractObject(const WText& InKey);
		~AInteractObject() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Interact Interface
		void OnBeginInteract(struct FHitResult_Box2D& HitResult) override;
		void OnEndInteract(struct FHitResult_Box2D& HitResult) override;
#pragma endregion

	protected:
		UBoxComponent* mBoxComponent;

	};
}

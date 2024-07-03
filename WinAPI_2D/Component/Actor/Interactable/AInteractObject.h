#pragma once
#include "Component/Actor/AActor.h"

namespace LJG
{
	class AInteractObject : public AActor, public IInteractableAPI
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Interact Interface
		void OnBeginInteract() override;
		void OnEndInteract() override;
#pragma endregion


	};
}

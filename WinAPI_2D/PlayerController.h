#pragma once
#include "CommonInclude.h"
#include "UObject.h"

namespace LJG
{
	class PlayerController : public UObject
	{
	public:
		PlayerController(const std::wstring& InTextureFile);
		~PlayerController();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void AddMovementInput(const FVector2f& MovementInputAmount) const;

	private:
	};
}

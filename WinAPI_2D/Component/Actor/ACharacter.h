#pragma once
#include "APawn.h"

namespace LJG
{
	class ACharacter : public APawn
	{
	public:
		explicit ACharacter(const WText& InKey);
		~ACharacter() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	};
}

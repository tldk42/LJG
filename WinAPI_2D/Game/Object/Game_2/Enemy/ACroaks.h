#pragma once
#include "Component/Actor/APawn.h"

namespace LJG
{
	class ACroaks: public APawn
	{
	public:
		ACroaks(const WText& InKey);
		~ACroaks() override;
		
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion
	};
}



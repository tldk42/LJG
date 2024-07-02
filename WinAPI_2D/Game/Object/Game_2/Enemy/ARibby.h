#pragma once
#include "Component/Actor/APawn.h"

namespace LJG
{
	class ARibby : public APawn
	{
	public:
		ARibby(const WText& InText);
		~ARibby() override;

	public:
		void Initialize() override;
		void Update(float DeltaTime) override;
	};
}

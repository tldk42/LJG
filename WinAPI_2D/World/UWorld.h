#pragma once
#include "Component/UObject.h"

namespace LJG
{
	class UWorld : public UObject
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		// static UWorld* g_World;

	protected:
		

	};
}

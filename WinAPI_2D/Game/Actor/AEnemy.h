#pragma once
#include "Component/Actor/APawn.h"
#include "Game/Interface/Interrfaces.h"

namespace LJG
{
	class AEnemy : public APawn, public IDamagable
	{
	public:
		AEnemy(const WText& InName);
		~AEnemy() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	public:
#pragma region IDamage Interface
		void  OnDead() override;
		void  OnHit(float InDamage) override;
		float GetCurrentHealth() override;
		float GetMaxHealth() override;
#pragma endregion

	protected:
		float_t mCurrentHP = 100.f;
	};

}

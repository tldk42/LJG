#include "AEnemy.h"

namespace LJG
{
	AEnemy::AEnemy(const WText& InName)
		: APawn(InName) {}

	AEnemy::~AEnemy() {}

	void AEnemy::Initialize()
	{
		APawn::Initialize();
	}

	void AEnemy::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}

	void AEnemy::OnDead() {}
	void AEnemy::OnHit(float InDamage) {}

	float AEnemy::GetCurrentHealth()
	{
		return mCurrentHP;
	}

	float AEnemy::GetMaxHealth()
	{
		return 0;
	}
}

#include "PeaShooter.h"

namespace LJG
{

	PeaShooter::PeaShooter()
	{
		
	}

	PeaShooter::~PeaShooter() {}

	void PeaShooter::Initialize()
	{
		AProjectile::Initialize();
	}

	void PeaShooter::Update(float DeltaTime)
	{
		AProjectile::Update(DeltaTime);
	}

	void PeaShooter::Render()
	{
		AProjectile::Render();
	}

	void PeaShooter::Release()
	{
		AProjectile::Release();
	}

	void PeaShooter::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		AProjectile::OnCollisionEnter(HitResult);
	}
}

#pragma once
#include "Component/Actor/AProjectile.h"

namespace LJG
{
	class PeaShooter : public AProjectile
	{
	public:
		PeaShooter();
		~PeaShooter() override;

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	protected:
		void OnCollisionEnter(FHitResult_Box2D& HitResult) override;

	};

}

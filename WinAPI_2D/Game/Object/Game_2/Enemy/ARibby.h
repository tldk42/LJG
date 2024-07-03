#pragma once
#include "Game/Actor/AEnemy.h"

namespace LJG::AI
{
	class RibbyBT;
}
namespace LJG
{
	#define Ribby ARibby::Get()

	class ARibby : public AEnemy, public TSingleton<ARibby>
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	public:
#pragma region IDamage Interface
		void OnDead() override;
		void OnHit(float InDamage) override;
#pragma endregion

	private:
		AI::RibbyBT* mBehaviorTree;

		friend class ACroaks;

	private:
		friend class TSingleton<ARibby>;
		ARibby();
		~ARibby() override;

	public:
		ARibby(const ARibby&)            = delete;
		ARibby& operator=(const ARibby&) = delete;
	};
}

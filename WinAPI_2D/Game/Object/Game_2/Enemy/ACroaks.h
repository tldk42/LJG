#pragma once
#include "Game/Actor/AEnemy.h"


namespace LJG
{
	#define Croaks ACroaks::Get()

	class ACroaks : public AEnemy, public TSingleton<ACroaks>
	{
	public:


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
		friend class ARibby;

	private:
		friend class TSingleton<ACroaks>;
		ACroaks();
		~ACroaks() override;

	public:
		ACroaks(const ACroaks&)            = delete;
		ACroaks& operator=(const ACroaks&) = delete;
	};
}

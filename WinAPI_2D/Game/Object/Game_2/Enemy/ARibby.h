#pragma once
#include "FTimer.h"
#include "data/MonsterData.h"
#include "Game/Actor/AEnemy.h"
#include "Helper/EngineHelper.h"

namespace LJG::AI
{
	class Game2BT;
}
namespace LJG
{
	#define Ribby ARibby::Get()

	class ARibby : public AEnemy, public IFrogInterface, public TSingleton<ARibby>
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

#pragma region Frog Interface
		uint8_t GetState() override;
		void    SetState(uint8_t NewState) override;
#pragma endregion

		inline bool IsRibbyTurn() const { return bIsRibbyTurn; }
		inline void SetTurn() { bIsRibbyTurn = true; }

		inline float_t GetElapsedSeconds() { return mTimer.ElapsedSeconds(); }

		void ResetCombo();
		void TryAttack_Punch();
		void CheckSpikeCoolTime();
		void TryAttack_Spike();
		void Roll(bool bLeft);
		void Punch();
		void SpikeBall();

	private:

		ERibbyState mCurrentState;

		FTimer  mTimer;
		float_t mLastLaunchTime    = 0.f;
		float_t mRollThresholdTime = 3.f;
		float_t mSpikeCoolTime     = 3.f;
		int32_t mMaxProjectile;
		int32_t mProjectileCounter = 0;
		bool    bIsRibbyTurn       = false;

		FVector2f mRollTarget = {-420.f * 1.5f, -157.f * 1.5f};

	private:
		friend class ACroaks;
		friend class Blackboard_Game2;
		friend class TSingleton<ARibby>;

		ARibby();
		~ARibby() override;

	public:
		ARibby(const ARibby&)            = delete;
		ARibby& operator=(const ARibby&) = delete;
	};
}

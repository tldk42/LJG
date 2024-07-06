#pragma once
#include "FTimer.h"
#include "Component/Actor/APawn.h"
#include "data/MonsterData.h"
#include "Game/Actor/AEnemy.h"


namespace LJG
{
	#define Croaks ACroaks::Get()

	class AWindSprite;

	class ACroaks : public AEnemy, public IFrogInterface, public TSingleton<ACroaks>
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

		void SetState(uint8_t NewState) override;
		void TryAttack_Spit();
		void Spit() const;

		inline float_t GetElapsedSeconds() { return mTimer.ElapsedSeconds(); }
#pragma endregion

		inline int32_t GetFanCounter() const { return mFanLoopCounter; }
		inline void    AddFanCounter() { mFanLoopCounter++; }

	private:
		ECroaksState mCurrentState;
		FTimer       mTimer;
		float_t      mLastLaunchTime = 0.f;
		int32_t      mFanLoopCounter = 0;

		AWindSprite* mWindImage;

	private:
		friend class ARibby;
		friend class TSingleton<ACroaks>;

		ACroaks();
		~ACroaks() override;

	public:
		ACroaks(const ACroaks&)            = delete;
		ACroaks& operator=(const ACroaks&) = delete;
	};
}

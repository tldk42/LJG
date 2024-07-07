#pragma once
#include "FTimer.h"
#include "data/MonsterData.h"
#include "Game/Actor/AEnemy.h"


namespace LJG
{

	#define SlotMachine ASlotMachine::Get()
	class UImage;

	class ASlotMachine : public AEnemy, public IFrogInterface, public TSingleton<ASlotMachine>
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

	public:
#pragma region Frog Interface
		uint8_t GetState() override;
		void    SetState(uint8_t NewState) override;

		inline float_t GetElapsedSeconds() { return mTimer.ElapsedSeconds(); }
#pragma endregion

		void SpitCoin();

	private:
		FTimer            mTimer;
		ESlotMachineState mCurrentState;

		UImage*   mSlots[3];
		FVector2f mSlotOffset = FVector2f(-78.f, -20.f);

	private:
		friend class ASlotMachine;
		friend class Blackboard_Game2;
		friend class TSingleton<ASlotMachine>;

		ASlotMachine();
		~ASlotMachine() override;

	public:
		ASlotMachine(const ASlotMachine&)            = delete;
		ASlotMachine& operator=(const ASlotMachine&) = delete;
	};
}

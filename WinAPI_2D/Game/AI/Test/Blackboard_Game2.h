#pragma once
#include "Component/Manager/Manager.h"
#include "data/MonsterData.h"

namespace LJG
{
#define BB_Game2 Blackboard_Game2::Get()

	struct Blackboard_Game2 : public TSingleton<Blackboard_Game2>
	{
	public:
		EGame2Phase CurrentPhase = EGame2Phase::Phase1;
		float_t     CurrentHP    = Game2MonsterHP[0];

	public:
		void ChangePhase() const;

	private:
		friend class TSingleton<Blackboard_Game2>;
		friend class ARibby;
		friend class ACroaks;
		friend class ASlotMachine;

		Blackboard_Game2()  = default;
		~Blackboard_Game2() = default;

	public:
		Blackboard_Game2(const Blackboard_Game2&)            = delete;
		Blackboard_Game2& operator=(const Blackboard_Game2&) = delete;
	};

}

#include "Ribby_Phase2.h"

#include "InputManager.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"

namespace LJG::AI
{
	Ribby_Phase2::Ribby_Phase2() {}

	ENodeState Ribby_Phase2::Evaluate()
	{
		switch (static_cast<ERibbyState>(Ribby.GetState()))
		{
		case ERibbyState::Idle:
			// Check 공격 가능
			Ribby.CheckSpikeCoolTime();
			return ENodeState::Running;
		case ERibbyState::Attack_Spike_Intro_Start:
			// 자동 Transition ->Spike Intro Loop
			return ENodeState::Running;
		case ERibbyState::Attack_Spike_Intro_Loop:
			// Check 공 던지기 가능
			Ribby.TryAttack_Spike();
			return ENodeState::Running;
		case ERibbyState::Attack_Spike_Loop:
			// 애니 메이션 Notify에서 공 던짐	
			return ENodeState::Running;
		}

		return ENodeState::Failure;
	}
}

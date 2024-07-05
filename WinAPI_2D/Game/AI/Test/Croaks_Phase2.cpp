#include "Croaks_Phase2.h"

#include "data/MonsterData.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Helper/EngineHelper.h"

namespace LJG::AI
{

	Croaks_Phase2::Croaks_Phase2() {}

	ENodeState Croaks_Phase2::Evaluate()
	{
		switch (static_cast<ECroaksState>(Croaks.GetState()))
		{
		case ECroaksState::Idle:
			// Check 공격 가능
			if (Croaks.GetElapsedSeconds() > 2.f)
			{
				Croaks.SetState(EnumAsByte(ECroaksState::Attack_Fan_Start));
			}
			return ENodeState::Running;
		case ECroaksState::Attack_Fan_Start:
			// 자동 Transition ->Spike Intro Loop
			return ENodeState::Running;
		case ECroaksState::Attack_Fan_Loop1:
			if (Croaks.GetFanCounter() >= 2)
				Croaks.SetState(EnumAsByte(ECroaksState::Attack_Fan_Loop2));
			return ENodeState::Running;
		case ECroaksState::Attack_Fan_Loop2:
			// 애니 메이션 Notify에서 공 던짐	
			return ENodeState::Running;
		}

		return ENodeState::Failure;
	}
}

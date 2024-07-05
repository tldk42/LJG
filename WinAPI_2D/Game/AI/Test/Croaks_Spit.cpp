#include "Croaks_Spit.h"

#include "InputManager.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Helper/EngineHelper.h"

namespace LJG::AI
{

	Croaks_Spit::Croaks_Spit()
		: Node("Test!")
	{}

	ENodeState Croaks_Spit::Evaluate()
	{
		/// Butterfly 작동 조건
		// 1. Croaks State & Ribby State != Intro
		if (Croaks.GetState() != 0 && Ribby.GetState() != 0)
		{
			// case 1: Ribby가 공격 모션을 이미 취하고 있음
			if (Croaks.GetState() == EnumAsByte(ECroaksState::Attack_Spit_Start))
			{
				// 이 상태에서는 Punch_Start 애님이 끝날 때 자동으로 Attack_Punch_Loop되도록 Notify 등록
				return ENodeState::Running;
			}
			// case 2: Ribby가 이미 Punch를 날리고 있음
			if (Croaks.GetState() == EnumAsByte(ECroaksState::Attack_Spit_Loop))
			{
				Croaks.TryAttack_Spit();

				return ENodeState::Running;
			}

			// case 3: Ribby & Croaks == Idle상태?
			if (Ribby.GetState() == EnumAsByte(ERibbyState::Idle) &&
				Croaks.GetState() == EnumAsByte(ERibbyState::Idle))
			{
				// case 3_1: Ribby Turn?
				if (!Ribby.IsRibbyTurn())
				{
					Croaks.SetState(EnumAsByte(ECroaksState::Attack_Spit_Start));
					return ENodeState::Running;
				}
			}
		}

		return ENodeState::Failure;

	}
}

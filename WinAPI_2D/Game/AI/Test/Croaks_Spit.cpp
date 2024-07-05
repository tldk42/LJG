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
		/// Butterfly �۵� ����
		// 1. Croaks State & Ribby State != Intro
		if (Croaks.GetState() != 0 && Ribby.GetState() != 0)
		{
			// case 1: Ribby�� ���� ����� �̹� ���ϰ� ����
			if (Croaks.GetState() == EnumAsByte(ECroaksState::Attack_Spit_Start))
			{
				// �� ���¿����� Punch_Start �ִ��� ���� �� �ڵ����� Attack_Punch_Loop�ǵ��� Notify ���
				return ENodeState::Running;
			}
			// case 2: Ribby�� �̹� Punch�� ������ ����
			if (Croaks.GetState() == EnumAsByte(ECroaksState::Attack_Spit_Loop))
			{
				Croaks.TryAttack_Spit();

				return ENodeState::Running;
			}

			// case 3: Ribby & Croaks == Idle����?
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

#include "Ribby_Fist.h"

#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Helper/EngineHelper.h"

namespace LJG::AI
{

	Ribby_Fist::Ribby_Fist()
		: Node("Test2!") {}

	ENodeState Ribby_Fist::Evaluate()
	{
		/// FirePunch �۵� ����
		// 1. Croaks State & Ribby State != Intro
		if (Croaks.GetState() != 0 && Ribby.GetState() != 0)
		{
			// case 1: Ribby�� ���� ����� �̹� ���ϰ� ����
			if (Ribby.GetState() == EnumAsByte(ERibbyState::Attack_Punch_Start))
			{
				// �� ���¿����� Punch_Start �ִ��� ���� �� �ڵ����� Attack_Punch_Loop�ǵ��� Notify ���
				return ENodeState::Running;
			}
			// case 2: Ribby�� �̹� Punch�� ������ ����
			if (Ribby.GetState() == EnumAsByte(ERibbyState::Attack_Punch_Loop))
			{
				Ribby.TryAttack_Punch();

				return ENodeState::Running;
			}

			// case 3: Ribby & Croaks == Idle����?
			if (Ribby.GetState() == EnumAsByte(ERibbyState::Idle) &&
				Croaks.GetState() == EnumAsByte(ERibbyState::Idle))
			{
				// case 3_1: Ribby Turn?
				if (Ribby.IsRibbyTurn())
				{
					Ribby.SetState(EnumAsByte(ERibbyState::Attack_Punch_Start));
					return ENodeState::Running;
				}
			}

			return ENodeState::Failure;

		}
		// 2.  && Ribby State == Idle 
		// 3. Ribby & Croaks Health > 0
		if (Ribby.GetState() == EnumAsByte(ERibbyState::Attack_Punch_Start))
		{
			if (Croaks.GetCurrentHealth() > 0.f)
			{
				Croaks.SetState(EnumAsByte(ECroaksState::Idle));
				return ENodeState::Success;
			}
		}

		return ENodeState::Failure;
	}
}

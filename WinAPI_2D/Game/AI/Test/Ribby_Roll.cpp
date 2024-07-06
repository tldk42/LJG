#include "Ribby_Roll.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"

namespace LJG::AI
{

	Ribby_Roll::Ribby_Roll(Text InName, const bool bLeft)
		: Node(std::move(InName)),
		  bLeftRoll(bLeft) {}

	ENodeState Ribby_Roll::Evaluate()
	{
		switch (static_cast<ERibbyState>(Ribby.GetState()))
		{
		case ERibbyState::Roll_Intro_Loop:
			if (Ribby.GetElapsedSeconds() > 1.5f)
			{
				Ribby.SetState(EnumAsByte(ERibbyState::Roll_Intro_End));
			}
			return ENodeState::Running;
		case ERibbyState::Roll_Loop:
			// Target ???? Roll
			Ribby.Roll(bLeftRoll);
			return ENodeState::Running;
		}

		return ENodeState::Failure;
	}
}

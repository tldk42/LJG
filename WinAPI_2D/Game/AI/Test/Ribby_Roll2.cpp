#include "Ribby_Roll2.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"

namespace LJG::AI
{

	Ribby_Roll2::Ribby_Roll2(Text InName)
		: Node(std::move(InName)) {}

	ENodeState Ribby_Roll2::Evaluate()
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
			// Target ÁöÁ¡ Roll
			Ribby.Roll(true);
			return ENodeState::Running;
		}

		return ENodeState::Failure;
	}
}

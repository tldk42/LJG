#include "FlyButterfly.h"

#include "InputManager.h"

namespace LJG::AI
{

	FlyButterfly::FlyButterfly()
		: Node("Test!")
	{
	}

	ENodeState FlyButterfly::Evaluate()
	{
		if (Manager_Input.IsKeyDown(EKeyCode::LButton))
		{
			LOG_CORE_INFO("FlyButterfly SUCCESS");
			return ENodeState::Success;
		}
		if (Manager_Input.IsKeyDown(EKeyCode::RButton))
		{
			LOG_CORE_INFO("FlyButterfly FAIL");
			return ENodeState::Failure;
		}
		else
		{
			return ENodeState::Running;
		}
	}
}

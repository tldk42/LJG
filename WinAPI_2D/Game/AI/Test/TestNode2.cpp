#include "TestNode2.h"

#include "InputManager.h"

namespace LJG::AI
{

	TestNode2::TestNode2()
		: Node("Test2!") {}

	ENodeState TestNode2::Evaluate()
	{
		if (Manager_Input.IsKeyDown(EKeyCode::RButton))
		{
			LOG_CORE_INFO("TestNode2 SUCCESS");
			return ENodeState::Success;
		}
		if (Manager_Input.IsKeyDown(EKeyCode::LButton))
		{
			LOG_CORE_INFO("TestNode2 FAIL");
			return ENodeState::Failure;
		}
		else
		{
			return ENodeState::Running;
		}
	}
}

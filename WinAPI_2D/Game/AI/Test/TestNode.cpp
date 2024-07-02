#include "TestNode.h"

#include "InputManager.h"

namespace LJG::AI
{

	TestNode::TestNode()
		: Node("Test!") {}

	ENodeState TestNode::Evaluate()
	{
		if (Manager_Input.IsKeyDown(EKeyCode::LButton))
		{
			LOG_CORE_INFO("TestNode SUCCESS");
			return ENodeState::Success;
		}
		if (Manager_Input.IsKeyDown(EKeyCode::RButton))
		{
			LOG_CORE_INFO("TestNode FAIL");
			return ENodeState::Failure;
		}
		else
		{
			return ENodeState::Running;
		}
	}
}

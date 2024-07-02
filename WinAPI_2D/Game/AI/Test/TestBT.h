#pragma once
#include "AI/BehaviorTree.h"

namespace LJG::AI
{
	class TestBT : public BehaviorTree
	{
	protected:
		Node* SetupTree() override;
	};
}

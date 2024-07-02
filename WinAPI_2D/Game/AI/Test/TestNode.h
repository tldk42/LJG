#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	class TestNode : public Node
	{
	public:
		TestNode();

	public:
		ENodeState Evaluate() override;
	};

}

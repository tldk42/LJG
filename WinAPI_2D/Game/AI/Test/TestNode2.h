#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	class TestNode2 : public Node
	{
	public:
		TestNode2();

	public:
		ENodeState Evaluate() override;
	};

}

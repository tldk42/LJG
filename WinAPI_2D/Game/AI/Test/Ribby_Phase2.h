#pragma once
#include "AI/Node.h"

namespace LJG::AI
{
	class Ribby_Phase2 : public Node
	{
	public:
		Ribby_Phase2();

	public:
		ENodeState Evaluate() override;
	};
}

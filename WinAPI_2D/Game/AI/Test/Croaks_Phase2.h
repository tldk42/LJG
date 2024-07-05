#pragma once
#include "AI/Node.h"

namespace LJG::AI
{
	class Croaks_Phase2 : public Node
	{
	public:
		Croaks_Phase2();

		ENodeState Evaluate() override;
	};

}

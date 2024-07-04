#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	class Fire_Punch : public Node
	{
	public:
		Fire_Punch();

	public:
		ENodeState Evaluate() override;
	};

}

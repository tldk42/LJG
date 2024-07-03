#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	class FlyButterfly : public Node
	{
	public:
		FlyButterfly();

	public:
		ENodeState Evaluate() override;
	};

}

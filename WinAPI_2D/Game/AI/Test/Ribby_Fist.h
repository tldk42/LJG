#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	class Ribby_Fist : public Node
	{
	public:
		Ribby_Fist();

	public:
		ENodeState Evaluate() override;
	};

}

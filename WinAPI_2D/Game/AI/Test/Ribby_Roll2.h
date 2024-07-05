#pragma once
#include "AI/Node.h"

namespace LJG::AI
{
	class Ribby_Roll2 : public Node
	{
	public:
		Ribby_Roll2(Text InName);

	public:
		ENodeState Evaluate() override;
	};

}

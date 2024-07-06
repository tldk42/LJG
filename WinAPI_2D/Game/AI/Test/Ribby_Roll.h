#pragma once
#include "AI/Node.h"

namespace LJG::AI
{
	class Ribby_Roll : public Node
	{
	public:
		Ribby_Roll(Text InName, const bool bLeft);

	public:
		ENodeState Evaluate() override;

	private:
		bool bLeftRoll;
	};

}

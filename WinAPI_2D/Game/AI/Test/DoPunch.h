#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	/** 작은 개구리가 펀치를 날린다. */
	class DoPunch : public Node
	{
	public:
		DoPunch();

	public:
		ENodeState Evaluate() override;
	};

}

#pragma once
#include "Node.h"

namespace LJG::AI
{
	class Selector : public Node
	{
	public:
		Selector(const Text& NodeName, const std::vector<Node*>& InChildNodes);
		~Selector() override;

		ENodeState Evaluate() override;
	};
}


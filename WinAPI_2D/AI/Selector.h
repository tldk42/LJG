#pragma once
#include "Node.h"

namespace LJG::AI
{
	class Selector : public Node
	{
	public:
		Selector(Text InText);
		Selector(const Text& NodeName, const std::vector<NodeSPtr>& InChildNodes);
		~Selector() override;

		ENodeState Evaluate() override;
	};
}


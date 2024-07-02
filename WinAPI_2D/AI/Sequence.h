#pragma once
#include "Node.h"

namespace LJG::AI
{
	class Sequence : public Node
	{
	public:
		Sequence(const Text& NodeName, const std::vector<Node*>& InChildNodes);
		~Sequence() override;

		ENodeState Evaluate() override;

	};

}

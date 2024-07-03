#include "Selector.h"

namespace LJG::AI
{

	Selector::Selector(Text InText)
		: Node(std::move(InText)){}

	Selector::Selector(const Text& NodeName, const std::vector<NodeSPtr>& InChildNodes)
		: Node(NodeName, InChildNodes) {}

	Selector::~Selector() {}

	ENodeState Selector::Evaluate()
	{
		for (const auto& node : ChildNodes)
		{
			switch (node->Evaluate())
			{
			case ENodeState::Failure:
				continue;
			case ENodeState::Success:
				NodeState = ENodeState::Success;
				return NodeState;
			case ENodeState::Running:
				NodeState = ENodeState::Running;
				return NodeState;
			default:
				continue;
			}
		}

		NodeState = ENodeState::Failure;
		return NodeState;
	}
}

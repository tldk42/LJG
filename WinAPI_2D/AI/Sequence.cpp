#include "Sequence.h"

namespace LJG::AI
{

	Sequence::Sequence(const Text& NodeName, const std::vector<NodeSPtr>& InChildNodes)
		: Node(NodeName, InChildNodes) {}

	Sequence::~Sequence() {}

	ENodeState Sequence::Evaluate()
	{
		bool bChildRunning = false;

		for (const auto& node : ChildNodes)
		{
			switch (node->Evaluate())
			{
			case ENodeState::Failure:
				NodeState = ENodeState::Failure;
				return NodeState;
			case ENodeState::Success:
				NodeState = ENodeState::Success;
				continue;
			case ENodeState::Running:
				bChildRunning = true;
				continue;
			default:
				NodeState = ENodeState::Success;
				return NodeState;
			}
		}

		NodeState = bChildRunning ? ENodeState::Running : ENodeState::Success;
		return NodeState;
	}
}

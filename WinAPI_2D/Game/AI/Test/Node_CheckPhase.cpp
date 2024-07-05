#include "Node_CheckPhase.h"

#include "Game/Object/Game_2/Enemy/ARibby.h"

namespace LJG::AI
{
	Node_CheckPhase::Node_CheckPhase(Text InName, const std::vector<NodeSPtr>& InChildNodes, const EGame2Phase Phase)
		: Node(std::move(InName), InChildNodes),
		  mPhase(Phase)
	{}

	ENodeState Node_CheckPhase::Evaluate()
	{
		// Phase1 & HP > 0?
		if (mPhase == Ribby.GetCurrentPhase() && Ribby.GetCurrentHealth() > 0.f)
		{
			for (const NodeSPtr& node : ChildNodes)
			{
				if (const ENodeState result = node->Evaluate(); result != ENodeState::Failure)
				{
					return result;
				}
			}
		}
		return ENodeState::Failure;
	}
}

#pragma once
#include "AI/Node.h"
#include "data/MonsterData.h"

namespace LJG::AI
{
	class Node_CheckPhase : public Node
	{
	public:
		Node_CheckPhase(Text InName, const std::vector<NodeSPtr>& InChildNodes, const EGame2Phase Phase);
		~Node_CheckPhase() override = default;

		ENodeState Evaluate() override;

	private:
		EGame2Phase mPhase;
	};

}

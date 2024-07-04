#include "RibbyBT.h"

#include "TestNode.h"
#include "DoPunch.h"
#include "Node_CheckPhase.h"
#include "AI/Selector.h"

namespace LJG::AI
{
	RibbyBT::RibbyBT(AActor* OwnerActor)
		: BehaviorTree(OwnerActor) {}

	RibbyBT::~RibbyBT() {}

	void RibbyBT::SetupTree()
	{
		mRootNode = std::make_shared<Selector>("Selector");
		mRootNode->SetNodes(
			std::vector<NodeSPtr>{
				std::make_shared<Node_CheckPhase>(
					"Phase1?", std::vector<NodeSPtr>{std::make_shared<Fire_Punch>(), std::make_shared<TestNode>()},
					EGame2Phase::Phase1),
				std::make_shared<Node_CheckPhase>("Phase2?", std::vector<NodeSPtr>{}, EGame2Phase::Phase2),
				std::make_shared<Node_CheckPhase>("Phase3?", std::vector<NodeSPtr>{}, EGame2Phase::Phase3)
			});
	}
}

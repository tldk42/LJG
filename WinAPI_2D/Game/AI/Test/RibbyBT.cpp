#include "RibbyBT.h"

#include "FlyButterfly.h"
#include "DoPunch.h"
#include "AI/Selector.h"
#include "AI/Sequence.h"

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
				//   ----------					 -------------
				// Punch ? ------------------------- Butterfly?
				std::make_shared<DoPunch>(), std::make_shared<FlyButterfly>()});
	}
}

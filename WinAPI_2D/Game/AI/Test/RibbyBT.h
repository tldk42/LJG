#pragma once
#include "AI/BehaviorTree.h"
#include "data/MonsterData.h"

namespace LJG::AI
{
	class RibbyBT : public BehaviorTree
	{
	public:
		RibbyBT(AActor* OwnerActor);
		~RibbyBT();

	

	protected:
		void        SetupTree() override;

	};
}

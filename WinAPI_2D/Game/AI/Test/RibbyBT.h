#pragma once
#include "AI/BehaviorTree.h"

namespace LJG
{
	class ARibby;
}
namespace LJG::AI
{
	class RibbyBT : public BehaviorTree
	{
	public:
		RibbyBT(AActor* OwnerActor);
		~RibbyBT();

	protected:
		void SetupTree() override;


	};
}

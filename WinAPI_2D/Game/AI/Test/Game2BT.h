#pragma once
#include "AI/BehaviorTree.h"
#include "data/MonsterData.h"

namespace LJG::AI
{
	class Game2BT : public BehaviorTree
	{
	public:
		Game2BT(const WText& InKey);
		~Game2BT() override = default;

	protected:
		void SetupTree() override;

	};
}

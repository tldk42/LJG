#include "Game2BT.h"

#include <memory>

#include "Croaks_Phase2.h"
#include "Croaks_Spit.h"
#include "Ribby_Fist.h"
#include "Node_CheckPhase.h"
#include "Ribby_Phase2.h"
#include "Ribby_Roll.h"
#include "Croaks_Morph.h"
#include "AI/Selector.h"
#include "AI/Sequence.h"

namespace LJG::AI
{
	Game2BT::Game2BT(const WText& InKey)
		: BehaviorTree(InKey) {}

	void Game2BT::SetupTree()
	{
		mRootNode = std::make_shared<Selector>("Selector");
		mRootNode->SetNodes(
			std::vector<NodeSPtr>{

				// Phase1은 개굴이 | 개골이가 한번씩 공격
				std::make_shared<Node_CheckPhase>(
					"Phase1?", /* | Decorator  <Phase 1> |*/ std::vector<NodeSPtr>{
						/*------------- /                           \-----------------*/
						/*-------------/                             \----------------*/
						/* -- Punch --/                               \-- Butterfly --*/
						std::make_shared<Ribby_Fist>(), std::make_shared<Croaks_Spit>()
					},
					EGame2Phase::Phase1),

				// Phase2는 같이 공격
				std::make_shared<Node_CheckPhase>(
					"Phase2?", std::vector<NodeSPtr>{
						std::make_shared<Ribby_Roll>("Change Roll!", true),
						std::make_shared<Sequence>(
							"Phase2",
							std::vector<NodeSPtr>{/* | Decorator  <Phase 2> |*/
								/*------------- /                           \-----------------*/
								/*-------------/                             \----------------*/
								/* -- Spike --/                               \--  Fanning  --*/
								std::make_shared<Ribby_Phase2>(), std::make_shared<Croaks_Phase2>()
							})
					}, EGame2Phase::Phase2),
				std::make_shared<Node_CheckPhase>(
					"Phase3?", std::vector<NodeSPtr>{
						std::make_shared<Selector>(
							"Roll Or SlotMachine", std::vector<NodeSPtr>
							{
								std::make_shared<Ribby_Roll>("Change Roll!", false)
								// std::make_shared<>()
							}),

						/*std::make_shared<Sequence>(
							"Phase2",
							std::vector<NodeSPtr>{/* | Decorator  <Phase 2> |#1#
								/*------------- /                           \-----------------#1#
								/*-------------/                             \----------------#1#
								/* -- Spike --/                               \--  Fanning  --#1#
								std::make_shared<Ribby_Phase2>(), std::make_shared<Croaks_Phase2>()
							})*/
					}, EGame2Phase::Phase3)
			});

	}
}

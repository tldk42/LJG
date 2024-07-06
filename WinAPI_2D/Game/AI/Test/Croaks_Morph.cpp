#include "Croaks_Morph.h"

#include "data/MonsterData.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"

namespace LJG::AI
{
	Croaks_Morph::Croaks_Morph(Text InName)
		: Node(std::move(InName)) {}

	ENodeState Croaks_Morph::Evaluate()
	{
		switch (static_cast<ECroaksState>(Croaks.GetState()))
		{
		case ECroaksState::Morph_Intro:
			return ENodeState::Running;
		case ECroaksState::Morph_Outro:
			return ENodeState::Running;
		}

		return ENodeState::Failure;
	}
}

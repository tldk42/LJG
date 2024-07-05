#include "Check_IsAlive.h"

#include "Game/Interface/Interrfaces.h"

namespace LJG::AI
{

	Check_IsAlive::Check_IsAlive(Text InName, IDamagable* InObj, const std::vector<NodeSPtr>& InChildNodes)
		: Node(InName, InChildNodes),
		  mObjToCheck(InObj) {}

	ENodeState Check_IsAlive::Evaluate()
	{
		if (mObjToCheck->GetCurrentHealth() > 0.f)
		{
			for (const NodeSPtr& node : ChildNodes)
			{
				if (const ENodeState result = node->Evaluate(); result != ENodeState::Failure)
				{
					return result;
				}
			}

			return ENodeState::Success;
		}
		return ENodeState::Failure;
	}
}

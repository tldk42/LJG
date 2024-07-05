#pragma once
#include "AI/Node.h"

class IDamagable;
namespace LJG::AI
{
	class Check_IsAlive : public Node
	{
	public:
		Check_IsAlive(Text InName, IDamagable* InObj, const std::vector<NodeSPtr>& InChildNodes = {});
		~Check_IsAlive() override = default;

		ENodeState Evaluate() override;

	private:
		IDamagable* mObjToCheck;
	};
}

#pragma once
#include "AI/Node.h"

namespace LJG::AI
{
	class Croaks_Morph : public Node
	{
	public:
		Croaks_Morph(Text InName);

	public:
		ENodeState Evaluate() override;
	};
}

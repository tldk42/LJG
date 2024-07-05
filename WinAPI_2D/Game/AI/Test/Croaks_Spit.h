#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	class Croaks_Spit : public Node
	{
	public:
		Croaks_Spit();

	public:
		ENodeState Evaluate() override;
	};

}

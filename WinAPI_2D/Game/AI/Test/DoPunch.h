#pragma once
#include "AI/Node.h"

namespace LJG::AI
{

	/** ���� �������� ��ġ�� ������. */
	class DoPunch : public Node
	{
	public:
		DoPunch();

	public:
		ENodeState Evaluate() override;
	};

}

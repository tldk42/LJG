#pragma once
#include <unordered_map>
#include <vector>

#include "CommonInclude.h"
#include "Enums.h"

namespace LJG::AI
{
	STRUCT_PTR(Node);

	struct Node
	{
	public:
		Node();
		Node(const Text& NodeName, const std::vector<Node*>& InChildNodes = {});
		virtual ~Node();

	public:
		virtual ENodeState Evaluate();

	public:
		void Attach(Node* InNode);

		void SetData(const Text& InName, UObject* Value);

		/** Ű-�� �����ϸ� ��ȯ (�θ���� Ž��) */
		UObject* GetData(const Text& InKey);
		/** �����忡 Ű-�� �����ϸ� ����� ������ �θ𿡼� ã���� �����. */
		bool ClearData(const Text& InKey);

		Node* GetRoot();

	public:
		Node*                              ParentNode = nullptr;
		ENodeState                         NodeState  = ENodeState::Failure;
		std::vector<Node*>                 ChildNodes;
		std::unordered_map<Text, UObject*> DataContext;

	};
}

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

		/** 키-값 존재하면 반환 (부모까지 탐색) */
		UObject* GetData(const Text& InKey);
		/** 현재노드에 키-값 존재하면 지우고 없으면 부모에서 찾으며 지운다. */
		bool ClearData(const Text& InKey);

		Node* GetRoot();

	public:
		Node*                              ParentNode = nullptr;
		ENodeState                         NodeState  = ENodeState::Failure;
		std::vector<Node*>                 ChildNodes;
		std::unordered_map<Text, UObject*> DataContext;

	};
}

#pragma once
#include <unordered_map>
#include <vector>

#include "CommonInclude.h"
#include "Enums.h"

namespace LJG::AI
{
	STRUCT_PTR(Node);

	struct Node : public std::enable_shared_from_this<Node>
	{
	public:
		Node();
		Node(Text InNodeName);
		Node(Text InNodeName, const std::vector<NodeSPtr>& InChildNodes);
		virtual ~Node();

	public:
		virtual ENodeState Evaluate();

	public:
		void SetNodes(const std::vector<NodeSPtr>& InChildNodes);

		void Attach(NodeSPtr InNode);

		void SetData(const Text& InName, UObject* Value);

		/** 키-값 존재하면 반환 (부모까지 탐색) */
		UObject* GetData(const Text& InKey);
		/** 현재노드에 키-값 존재하면 지우고 없으면 부모에서 찾으며 지운다. */
		bool ClearData(const Text& InKey);

		NodeSPtr GetRoot();

	public:
		AActor*                            Owner;
		Text                               NodeName;
		NodeWPtr                           ParentNode;
		ENodeState                         NodeState = ENodeState::Failure;
		std::vector<NodeSPtr>              ChildNodes;
		std::unordered_map<Text, UObject*> DataContext;

	};
}

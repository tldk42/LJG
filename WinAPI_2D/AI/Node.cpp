#include "Node.h"
namespace LJG::AI
{

	Node::Node()
		: ParentNode(nullptr)
	{}

	Node::Node(const Text& NodeName, const std::vector<Node*>& InChildNodes)
	{
		for (Node* node : InChildNodes)
		{
			Attach(node);
		}
	}

	Node::~Node()
	{
		
	}

	ENodeState Node::Evaluate()
	{
		return ENodeState::Failure;
	}

	void Node::Attach(Node* InNode)
	{
		InNode->ParentNode = this;
		ChildNodes.emplace_back(InNode);
	}

	void Node::SetData(const Text& InName, UObject* Value)
	{
		if (!DataContext.contains(InName))
		{
			DataContext[InName] = Value;
		}
		else
		{
			LOG_CORE_WARN("이미 존재하는 키값에 삽입 시도");
		}
	}

	UObject* Node::GetData(const Text& InKey)
	{
		if (DataContext.contains(InKey))
		{
			return DataContext[InKey];
		}

		Node* node = ParentNode;

		while (node != nullptr)
		{
			if (UObject* value = node->GetData(InKey); value != nullptr)
				return value;
			node = node->ParentNode;
		}

		return nullptr;
	}

	bool Node::ClearData(const Text& InKey)
	{
		if (DataContext.contains(InKey))
		{
			DataContext.erase(InKey);
			return true;
		}

		Node* node = ParentNode;
		while (node != nullptr)
		{
			if (bool cleared = node->ClearData(InKey))
				return true;
			node = node->ParentNode;
		}

		return false;
	}

	Node* Node::GetRoot()
	{
		Node* node = this;
		while (node->ParentNode != nullptr)
		{
			node = node->ParentNode;
		}

		return node;
	}
}

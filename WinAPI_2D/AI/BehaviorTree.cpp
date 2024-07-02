#include "BehaviorTree.h"

namespace LJG::AI
{

	BehaviorTree::BehaviorTree() {}
	BehaviorTree::~BehaviorTree() {}

	void BehaviorTree::Initialize()
	{
		mRootNode = SetupTree();
	}

	void BehaviorTree::Update(float DeltaTime)
	{
		if (mRootNode)
		{
			mRootNode->Evaluate();
		}
	}

	void BehaviorTree::Render() {}

	void BehaviorTree::Release()
	{
		for (auto& node : mRootNode->ChildNodes)
		{
			delete node;
			node = nullptr;
		}
	}
}

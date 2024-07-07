#include "BehaviorTree.h"

namespace LJG::AI
{

	BehaviorTree::BehaviorTree(const WText& InKey)
		: UObject(InKey)
	{}

	BehaviorTree::~BehaviorTree()
	{
		Release();
	}

	void BehaviorTree::Initialize()
	{
		SetupTree();
		mRootNode->Owner = mOwnerActor;
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
		mRootNode.reset();
	}
}

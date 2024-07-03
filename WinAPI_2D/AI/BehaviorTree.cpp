#include "BehaviorTree.h"

namespace LJG::AI
{

	BehaviorTree::BehaviorTree(AActor* OwnerActor)
	{
		mOwnerActor = OwnerActor;
	}

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

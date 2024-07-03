#pragma once
#include "Node.h"
#include "Component/UObject.h"

namespace LJG::AI
{
	class BehaviorTree : public UObject
	{
	public:
		BehaviorTree(AActor* OwnerActor);
		~BehaviorTree() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	protected:
		virtual void SetupTree() = 0;

	protected:
		NodeSPtr mRootNode;
	};
}

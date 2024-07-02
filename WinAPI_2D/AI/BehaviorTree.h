#pragma once
#include "CommonInclude.h"
#include "Node.h"

namespace LJG::AI
{
	class BehaviorTree : public ICoreAPI
	{
	public:
		BehaviorTree();
		~BehaviorTree() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	protected:
		virtual Node* SetupTree() = 0;

	protected:
		Node* mRootNode;
	};
}

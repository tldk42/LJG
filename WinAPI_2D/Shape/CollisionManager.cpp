#include "CollisionManager.h"
#include "Shape/UBoxComponent.h"
#include "Component/Manager/SceneManager.h"

namespace LJG
{
	void CollisionManager::EnrollLayer(UBoxComponent* InComponent)
	{
		static_assert(std::is_base_of_v<ICollisionAPI, UBoxComponent>, "ICollisionAPI 상속!");
		mLayerMap[InComponent->GetTraceType()].emplace_back(InComponent);
	}

	void CollisionManager::ReleaseLayer(UBoxComponent* InComponent)
	{
		// static_assert(std::is_base_of_v<ICollisionAPI, UBoxComponent>, "ICollisionAPI 상속!");
		//
		// if (InComponent)
		// {
		// 	if (const ETraceType traceType = InComponent->GetTraceType(); mLayerMap.contains(traceType))
		// 	{
		// 		auto it = std::ranges::find(mLayerMap[traceType], InComponent);
		// 		if (it != mLayerMap[traceType].end())
		// 		{
		// 			mLayerMap[traceType].erase(it);
		// 		}
		// 	}
		// }
	}

	void CollisionManager::Initialize() {}

	void CollisionManager::Update(float DeltaTime)
	{
		UScene* scene = Manager_Scene.GetCurrentScene();

		for (UINT row = 0; row < static_cast<UINT>(ETraceType::Max); ++row)
		{
			for (UINT col = 0; col < static_cast<UINT>(ETraceType::Max); ++col)
			{
				if (mCollisionLayerMatrix[row][col])
				{
					LayerCollision(scene, static_cast<ETraceType>(row), static_cast<ETraceType>(col));
				}
			}
		}
	}

	void CollisionManager::Render()
	{
		// TODO: 렌더 ON / OFF
	}

	void CollisionManager::Release()
	{
		for (auto& bitSet : mCollisionLayerMatrix)
		{
			bitSet.reset();
		}
		mLayerMap.clear();
		mCollisionMap.clear();
	}

	void CollisionManager::EnableLayerCheck(ETraceType Left, ETraceType Right, bool bEnable)
	{
		int row = 0;
		int col = 0;

		row = static_cast<UINT>(Left);
		col = static_cast<UINT>(Right);
		// if (Left <= Right)
		// {
		// 	row = static_cast<UINT>(Left);
		// 	col = static_cast<UINT>(Right);
		// }
		// else
		// {
		// 	row = static_cast<UINT>(Right);
		// 	col = static_cast<UINT>(Left);
		// }

		mCollisionLayerMatrix[row][col] = bEnable;
	}

	bool CollisionManager::Intersaect(UBoxComponent* InLeft, UBoxComponent* InRight)
	{
		if (InLeft && InRight)
		{
			return InLeft->GetBox().Intersect(InRight->GetBox());
		}
		return false;
	}

	void CollisionManager::ColliderCollision(UBoxComponent* Left, UBoxComponent* Right)
	{

		CollisionID id{};
		id.Left  = Left->GetCollisionID();
		id.Right = Right->GetCollisionID();

		if (!mCollisionMap.contains(id.ID))
		{
			mCollisionMap[id.ID] = false;
		}

		FHitResult_Box2D hitResult{};
		hitResult.Src  = Left;
		hitResult.Dest = Right;

		if (Intersaect(Left, Right))
		{
			const FBox2f overlappedBox = Left->GetBox().Overlap(Right->GetBox());

			hitResult.OverlappedBox = overlappedBox;
			hitResult.Distance      = FVector2f::Distance(overlappedBox.Max, overlappedBox.Min);

			if (mCollisionMap[id.ID])
			{
				Left->OnCollision(hitResult);
				Right->OnCollision(hitResult);
			}
			else
			{
				Left->OnCollisionEnter(hitResult);
				Right->OnCollisionEnter(hitResult);
				mCollisionMap[id.ID] = true;
			}
		}
		else
		{
			if (mCollisionMap[id.ID])
			{
				Left->OnCollisionExit(hitResult);
				Right->OnCollisionExit(hitResult);

				mCollisionMap[id.ID] = false;
			}
		}
	}

	void CollisionManager::LayerCollision(UScene* InScene, ETraceType InRow, ETraceType InCol)
	{
		const std::vector<UBoxComponent*>& leftLayers  = mLayerMap[InRow];
		const std::vector<UBoxComponent*>& rightLayers = mLayerMap[InCol];


		for (UBoxComponent* leftLayer : leftLayers)
		{
			for (UBoxComponent* rightLayer : rightLayers)
			{
				if (leftLayer->IsActive() && rightLayer->IsActive())
				{
					if (leftLayer != rightLayer)
					{
						ColliderCollision(leftLayer, rightLayer);
					}
				}
			}
		}
	}
}

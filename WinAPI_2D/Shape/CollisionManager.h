#pragma once
#include <bitset>

#include "Component/Manager/Manager.h"
#include "Component/Scene/UScene.h"

namespace LJG
{
	#define Manager_Collision CollisionManager::Get()

	class USceneComponent;
	class UBoxComponent;

	struct FHitResult
	{
		USceneComponent* HitComponent;
		FVector2f        HitPoint;
		float_t          Distance;
	};

	struct FHitResult_Box2D
	{
		UBoxComponent* Src;
		UBoxComponent* Dest;
		FBox2f         OverlappedBox{};
		float_t        Distance = -1.f;
	};

	union CollisionID
	{
		struct
		{
			UINT Left;
			UINT Right;
		};

		UINT64 ID;
	};

	class CollisionManager : public TSingleton<CollisionManager>, public ICoreAPI
	{
	public:
		void EnrollLayer(UBoxComponent* InComponent);
		void ReleaseLayer(UBoxComponent* InComponent);

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		void EnableLayerCheck(ETraceType Left, ETraceType Right, bool bEnable);

	private:
		static bool Intersaect(UBoxComponent* InLeft, UBoxComponent* InRight);
		void        ColliderCollision(UBoxComponent* Left, UBoxComponent* Right);
		void        LayerCollision(UScene* InScene, ETraceType InRow, ETraceType InCol);

	private:
		std::bitset<static_cast<UINT>(ETraceType::Max)> mCollisionLayerMatrix[static_cast<UINT>(ETraceType::Max)];
		std::unordered_map<ETraceType, std::vector<UBoxComponent*>>
		mLayerMap;  // 모든 타입에 대해 오브젝트를 가지고있어야한다. TODO: BoxComponent보다 상위 Base 클래스 만들기
		std::unordered_map<uint64_t, bool> mCollisionMap;
	};


	/*// Trace
inline bool LineTrace2Box(const FVector2f& Origin, const FVector2f& Destination, const ETraceType InTypeFilter,
						  FHitResult&      OutHitResult)
{
	bool bIntersected = false;
	for (UBoxComponent* box : BoxTypes.GetShapes())
	{
		if (box->GetTraceType() != InTypeFilter)
			continue;
		FVector2f   Intersection;
		Math::TLine Line(Origin, Destination);
		auto        Edges = box->GetBox().GetEdges();

		for (const auto& Edge : Edges)
		{
			Math::TLine EdgeLine(Edge.first, Edge.second);

			if (Line.Intersect(EdgeLine, Intersection))
			{
				float Dist = (Intersection - Origin).GetLength();
				if (bIntersected && Dist < OutHitResult.Distance)
				{

					OutHitResult.HitComponent = box;
					OutHitResult.HitPoint     = Intersection;
					OutHitResult.Distance     = Dist;
				}
				else
				{
					OutHitResult.HitComponent = box;
					OutHitResult.HitPoint     = Intersection;
					OutHitResult.Distance     = Dist;
					bIntersected              = true;
				}
			}
		}
	}
	return bIntersected;
}*/
}

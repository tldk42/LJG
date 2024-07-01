#pragma once
#include "UBoxComponent.h"
#include "Component/Manager/Manager.h"

namespace LJG
{
	class USceneComponent;
	#define LineTypes Tracer<ULineComponent>::Get()
	#define BoxTypes Tracer<UBoxComponent>::Get()

	struct FHitResult
	{
		USceneComponent* HitComponent;
		FVector2f        HitPoint;
		float_t          Distance;
	};

	template <class ShapeType>
	class Tracer : public TSingleton<Tracer<ShapeType>>
	{
	public:
		void AddComponent(ShapeType* Comp)
		{
			mPrimitiveType.emplace_back(Comp);
		}

		void RemoveComponent(ShapeType* Comp)
		{
			auto it = std::find(mPrimitiveType.begin(), mPrimitiveType.end(), Comp);
			if (it != mPrimitiveType.end())
			{
				mPrimitiveType.erase(it);
			}
		};

		const std::vector<ShapeType*>& Types() const { return mPrimitiveType; }

	private:
		std::vector<ShapeType*> mPrimitiveType;
	};

	// Trace
	inline bool LineTrace2Box(const FVector2f& Origin, const FVector2f& Destination, const ETraceType InTypeFilter,
							  FHitResult&      OutHitResult)
	{
		bool bIntersected = false;
		for (UBoxComponent* box : BoxTypes.Types())
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
	}
}

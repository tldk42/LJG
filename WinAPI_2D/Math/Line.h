#pragma once
#include "MathFwd.h"
#include "Vector2D.h"

namespace LJG
{
	namespace Math
	{
		class TLine
		{
		public:
			FVector2f Origin;
			FVector2f Target;

		public:
			TLine() = default;

			TLine(const FVector2f& InOrigin, const FVector2f& InTarget)
				: Origin(InOrigin),
				  Target(InTarget) {}

		public:
			inline bool Intersect(const TLine& Other, FVector2f& OutIntersection) const
			{
				FVector2f B   = Target - Origin;
				FVector2f D   = Other.Target - Other.Origin;
				float     BxD = FVector2f::CrossProduct(B, D);

				if (BxD == 0) // ÆòÇà
					return false;

				FVector2f C = Other.Origin - Origin;
				float     t = FVector2f::CrossProduct(C, D) / BxD;
				float     u = FVector2f::CrossProduct(C, B) / BxD;

				if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
				{
					OutIntersection = Origin + B * t;
					return true;
				}

				return false;
			}
		};
	}
}

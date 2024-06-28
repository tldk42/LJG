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

		};
	}
}

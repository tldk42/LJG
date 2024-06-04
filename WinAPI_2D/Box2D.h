#pragma once
#include <assert.h>

#include "Math/Vector2D.h"
#include <vector>

namespace LJG
{
	namespace Math
	{
		template <typename T>
		struct TBox2
		{
		public:
			using FReal = T;


			TVector2<T> Min;
			TVector2<T> Max;

			bool bIsValid;

		public:
			TBox2() = default;

			TBox2(const TVector2<T>& InMin, const TVector2<T>& InMax)
				: Min(InMin),
				  Max(InMax),
				  bIsValid(true) {}

			TBox2<T>(const TVector2<T>* Points, const int32_t Count);

			TBox2<T>(const std::vector<TVector2<T>>& Points);

		public:
			bool operator==(const TBox2& Other) const
			{
				return (Min == Other.Min) && (Max == Other.Max);
			}

			bool operator!=(const TBox2& Other) const
			{
				return !(*this == Other);
			}

			TVector2<T>& operator[](int32_t Index)
			{
				assert((Index >= 0) && (Index < 2));

				if (Index == 0)
				{
					return Min;
				}

				return Max;
			}

		public:
			TBox2<T>    Overlap(const TBox2<T>& Other) const;
			inline bool Intersect(const TBox2<T>& Other) const;
		};

		template <typename T> TBox2<T> TBox2<T>::Overlap(const TBox2<T>& Other) const
		{
			if (!Intersect(Other))
			{
				static TBox2<T> EmptyBox;
				return EmptyBox;
			}

			TVector2<T> MinVector, MaxVector;

			// MinVector.X = 
		}

		template <typename T> bool TBox2<T>::Intersect(const TBox2<T>& Other) const
		{
			if ((Min.X > Other.Max.X) || (Other.Min.X > Max.X))
			{
				return false;
			}

			if ((Min.Y > Other.Max.Y) || (Other.Min.Y > Max.Y))
			{
				return false;
			}

			return true;
		}
	}
}

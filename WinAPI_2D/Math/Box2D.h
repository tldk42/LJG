#pragma once
#include <assert.h>
#include "Vector2D.h"
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

			bool Equals(const TBox2<T>& Other, T Tolerance = M_KINDA_SMALL_NUMBER) const
			{
				return Min == Other.Min && Max == Other.Max;
			}

			inline TBox2<T>& operator+=(const TVector2<T>& Other);

			inline TBox2<T>& operator+=(const TBox2<T>& Other);

			TBox2<T> operator+(const TBox2<T>& Other) const
			{
				return TBox2<T>(*this) += Other;
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

			inline std::vector<std::pair<TVector2<T>, TVector2<T>>> GetEdges() const
			{
				return {
					{Min, TVector2<T>(Max.X, Min.Y)}, // 상단
					{TVector2<T>(Max.X, Min.Y), Max}, // 우측
					{Max, TVector2<T>(Min.X, Max.Y)}, // 하단
					{TVector2<T>(Min.X, Max.Y), Min}  // 좌측
				};
			}
		};

		template <typename T> TBox2<T>::TBox2(const TVector2<T>* Points, const int32_t Count)
			: Min(0.f, 0.f),
			  Max(0.f, 0.f),
			  bIsValid(false)
		{
			for (int32_t PointItr = 0; PointItr < Count; ++PointItr)
			{
				*this += Points[PointItr];
			}
		}

		template <typename T> TBox2<T>::TBox2(const std::vector<TVector2<T>>& Points)
			: Min(0.f, 0.f),
			  Max(0.f, 0.f),
			  bIsValid(false)
		{
			for (const TVector2<T>& EachPoint : Points)
			{
				*this += EachPoint;
			}
		}

		template <typename T> TBox2<T>& TBox2<T>::operator+=(const TVector2<T>& Other)
		{
			if (bIsValid)
			{
				Min.X = FMath::Min(Min.X, Other.X);
				Min.Y = FMath::Min(Min.Y, Other.Y);

				Max.X = FMath::Max(Max.X, Other.X);
				Max.Y = FMath::Max(Max.Y, Other.Y);
			}
			else
			{
				Min      = Max = Other;
				bIsValid = true;
			}

			return *this;
		}

		template <typename T> TBox2<T>& TBox2<T>::operator+=(const TBox2<T>& Other)
		{
			if (bIsValid && Other.bIsValid)
			{
				Min.X = FMath::Min(Min.X, Other.Min.X);
				Min.Y = FMath::Min(Min.Y, Other.Min.Y);

				Max.X = FMath::Max(Max.X, Other.Max.X);
				Max.Y = FMath::Max(Max.Y, Other.Max.Y);
			}
			else if (Other.bIsValid)
			{
				*this = Other;
			}

			return *this;
		}

		template <typename T> TBox2<T> TBox2<T>::Overlap(const TBox2<T>& Other) const
		{
			if (!Intersect(Other))
			{
				static TBox2<T> EmptyBox;
				return EmptyBox;
			}

			TVector2<T> MinVector, MaxVector;

			MinVector.X = FMath::Max(Min.X, Other.Min.X);
			MinVector.Y = FMath::Max(Min.Y, Other.Min.Y);

			MaxVector.X = FMath::Min(Max.X, Other.Max.X);
			MaxVector.Y = FMath::Min(Max.Y, Other.Max.Y);

			return TBox2<T>(MinVector, MaxVector);
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

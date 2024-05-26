#pragma once

namespace LJG
{
	namespace Math
	{
		template <typename T>
		struct TVector;
		template <typename T>
		struct TVector2;
	}
}

using FVector = LJG::Math::TVector<double>;
using FVector2D = LJG::Math::TVector2<double>;

using FVector3d = LJG::Math::TVector<double>;
using FVector2d = LJG::Math::TVector2<double>;

using FVector3f = LJG::Math::TVector<float>;
using FVector2f = LJG::Math::TVector2<float>;

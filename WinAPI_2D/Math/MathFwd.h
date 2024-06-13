#pragma once

namespace LJG::Math
{
	template <typename T>
	struct TVector;
	template <typename T>
	struct TVector2;


	template <typename T>
	struct TBox2;

	template <typename T>
	struct TTransform;

}

using FVector = LJG::Math::TVector<double>;
using FVector2D = LJG::Math::TVector2<double>;

using FVector3d = LJG::Math::TVector<double>;
using FVector2d = LJG::Math::TVector2<double>;

using FVector3f = LJG::Math::TVector<float>;
using FVector2f = LJG::Math::TVector2<float>;

using FBox2f = LJG::Math::TBox2<float>;
using FBox2D = LJG::Math::TBox2<double>;

using FTransform2d = LJG::Math::TTransform<double>;
using FTransform2f = LJG::Math::TTransform<float>;

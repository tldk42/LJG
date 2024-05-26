#include "Vector.h"

template<> const FVector3f FVector3f::ZeroVector(0, 0, 0);
template<> const FVector3f FVector3f::OneVector(1, 1, 1);
template<> const FVector3f FVector3f::UpVector(0, 0, 1);
template<> const FVector3f FVector3f::DownVector(0, 0, -1);
template<> const FVector3f FVector3f::ForwardVector(1, 0, 0);
template<> const FVector3f FVector3f::BackwardVector(-1, 0, 0);
template<> const FVector3f FVector3f::RightVector(0, 1, 0);
template<> const FVector3f FVector3f::LeftVector(0, -1, 0);
template<> const FVector3f FVector3f::XAxisVector(1, 0, 0);
template<> const FVector3f FVector3f::YAxisVector(0, 1, 0);
template<> const FVector3f FVector3f::ZAxisVector(0, 0, 1);
template<> const FVector3d FVector3d::ZeroVector(0, 0, 0);
template<> const FVector3d FVector3d::OneVector(1, 1, 1);
template<> const FVector3d FVector3d::UpVector(0, 0, 1);
template<> const FVector3d FVector3d::DownVector(0, 0, -1);
template<> const FVector3d FVector3d::ForwardVector(1, 0, 0);
template<> const FVector3d FVector3d::BackwardVector(-1, 0, 0);
template<> const FVector3d FVector3d::RightVector(0, 1, 0);
template<> const FVector3d FVector3d::LeftVector(0, -1, 0);
template<> const FVector3d FVector3d::XAxisVector(1, 0, 0);
template<> const FVector3d FVector3d::YAxisVector(0, 1, 0);
template<> const FVector3d FVector3d::ZAxisVector(0, 0, 1);


template<> const FVector2f FVector2f::ZeroVector(0, 0);
template<> const FVector2f FVector2f::UnitVector(1, 1);
template<> const FVector2f FVector2f::Unit45Deg(M_INVERSE_SQRT_2, M_INVERSE_SQRT_2);
template<> const FVector2d FVector2d::ZeroVector(0, 0);
template<> const FVector2d FVector2d::UnitVector(1, 1);
template<> const FVector2d FVector2d::Unit45Deg(M_INVERSE_SQRT_2, M_INVERSE_SQRT_2);
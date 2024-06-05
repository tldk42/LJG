#define M_PI  (3.1415926535897932f)
#define M_SMALL_NUMBER (0.00000001)
#define M_KINDA_SMALL_NUMBER (0.0001)
#define M_BIG_NUMBER (340000000000000000000000000000000000000)
#define M_INVERSE_SQRT_2	(0.70710678118654752440084436210485f)

#pragma once
class FMath
{
	// [[nodiscard]] static inline bool IsNearlyEqual(float A, float B, float ErrorTolerance = M_SMALL_NUMBER)
	// {
	// 	return abs(A - B) <= ErrorTolerance;
	// }
public:
	template <typename T>
	[[nodiscard]] static constexpr inline T Max(const T A, const T B)
	{
		return (B < A) ? A : B;
	}

	template <typename T>
	[[nodiscard]] static constexpr inline T Max3(const T A, const T B, const T C)
	{
		return Max(Max(A, B), C);
	}

	template <typename T>
	[[nodiscard]] static constexpr inline T Min(const T A, const T B)
	{
		return (B > A) ? A : B;
	}
};

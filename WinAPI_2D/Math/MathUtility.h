#define M_PI  (3.1415926535897932f)
#define M_SMALL_NUMBER (0.00000001)
#define M_KINDA_SMALL_NUMBER (0.0001)
#define M_BIG_NUMBER (340000000000000000000000000000000000000)
#define M_INVERSE_SQRT_2	(0.70710678118654752440084436210485f)

#pragma once
#include <random>

struct FMath
{
	[[nodiscard]] static inline bool IsNearlyEqual(float A, float B, float ErrorTolerance = M_SMALL_NUMBER)
	{
		return Abs(A - B) <= ErrorTolerance;
	}

	//----------------------- Min Max ------------------------------------
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


	//------------------------- Clamp --------------------------------
	template <typename T>
	[[nodiscard]] static constexpr inline T Clamp(const T Current, const T MinValue, const T MaxValue)
	{
		return Max(Min(Current, MaxValue), MinValue);
	}

	[[nodiscard]] static constexpr inline float Clamp(const float Current, const float MinValue, const float MaxValue)
	{
		return Clamp<float>(Current, MinValue, MaxValue);
	}

	template <typename T>
	static constexpr inline T Abs(const T A)
	{
		return (A < static_cast<T>(0)) ? -A : A;
	}


	//--------------------------- Lerp -------------------------------------------
	template <typename T, typename U>
	[[nodiscard]] static inline constexpr T Lerp(const T Current, const T Target, const U Alpha)
	{
		return (T)(Current + ((Target - Current) * Alpha));
	}

	template <typename T>
	static bool Sign(T A)
	{
		return A >= 0;
	};

	//--------------------------- Rand Generator -------------------------------------------
	static float_t GenerateRandomfloat(float_t InMin, float_t InMax)
	{
		// 랜덤 장치를 초기화합니다.
		std::random_device rd;
		// 랜덤 숫자 생성기를 초기화합니다.
		std::mt19937 gen(rd());
		// 주어진 범위 내에서 부동 소수점 숫자를 생성하는 분포를 정의합니다.
		std::uniform_real_distribution dis(InMin, InMax);


		// 랜덤 부동 소수점 숫자를 반환합니다.
		return dis(gen);
	}

	static int32_t GenerateNum(int32_t InMin, int32_t InMax)
	{
		// 랜덤 장치를 초기화합니다.
		std::random_device rd;
		// 랜덤 숫자 생성기를 초기화합니다.
		std::mt19937 gen(rd());
		// 주어진 범위 내에서 부동 소수점 숫자를 생성하는 분포를 정의합니다.
		std::uniform_int_distribution dis(InMin, InMax);


		// 랜덤 부동 소수점 숫자를 반환합니다.
		return dis(gen);
	}
};

#pragma once
#include <chrono>

#include "CommonInclude.h"

namespace LJG
{
	constexpr float TickFrequency = 60 / 1000.f;

	using namespace std::chrono;

	class UTimer
	{
	public:
		UTimer();

		// static bool  Initialize();
		// static void  Update();
		// static void  Render(HDC Hdc);
		// static float GetFPS() { return 1.f / DeltaTimeValue; }

		void Reset();

		/** 경과 시간 (초) 반환*/
		float ElapsedSeconds();

		/** 1/1000초 반환 */
		float ElapsedMillis();

	private:
		time_point<high_resolution_clock> mStartTime;

		// static LARGE_INTEGER CpuFrequency;// CPU 고유 주파수
		// static LARGE_INTEGER PrevFrequency; // 이전 클럭 진동
		// static LARGE_INTEGER CurrentFrequency; // 현재 클럭 진동
	};
}

#include "UTimer.h"

namespace LJG
{
	// LARGE_INTEGER UTimer::CpuFrequency     = {};
	// LARGE_INTEGER UTimer::PrevFrequency    = {};
	// LARGE_INTEGER UTimer::CurrentFrequency = {};

	UTimer::UTimer()
	{
		Reset();
	}

	/*
	bool UTimer::Initialize()
	{
		QueryPerformanceFrequency(&CpuFrequency);

		if (CpuFrequency.QuadPart == 0)
		{
			LOG_CORE_WARN("고해상도타이머 지원 X");
			return false;
		}

		QueryPerformanceFrequency(&PrevFrequency);

		mUpdateTimer = ElapsedMillis();

		return true;
	}

	void UTimer::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency); // 현재 클럭 진동(Perforrmance)값 반환

		// (현재 - 이전) 진동 수 (QuadPart)가 실제 값
		const float differentFreq = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		// (현재 - 이전) 카운터 / 고유 주파수로 나눈 값 
		DeltaTimeValue = differentFreq / static_cast<float>(CpuFrequency.QuadPart);

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}

	void UTimer::Render(HDC Hdc)
	{
		static float time = 0.f;
		time += DeltaTimeValue;


		const float fps = 1.f / DeltaTimeValue;
	}*/


	void UTimer::Reset()
	{
		mStartTime = high_resolution_clock::now();
	}

	float UTimer::ElapsedSeconds()
	{
		return ElapsedMillis() / 1000.f;
	}

	float UTimer::ElapsedMillis()
	{
		return duration_cast<duration<float, std::milli>>(high_resolution_clock::now() - mStartTime).count();
	}
}

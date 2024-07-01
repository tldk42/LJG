#include "FTimer.h"

namespace LJG
{
	FTimer::FTimer()
	{
		Reset();
	}

	void FTimer::Reset()
	{
		mStartTime = high_resolution_clock::now();
	}

	float FTimer::ElapsedSeconds()
	{
		return ElapsedMillis() / 1000.f;
	}

	float FTimer::ElapsedMillis()
	{
		return duration_cast<duration<float, std::milli>>(high_resolution_clock::now() - mStartTime).count();
	}

	void FTimer::SetTimer(std::function<void()> Callback, float InDelaySeconds)
	{
		std::thread([Callback, InDelaySeconds](){
			std::this_thread::sleep_for(std::chrono::duration<float_t>(InDelaySeconds));
			Callback();
		}).detach();
	}
}

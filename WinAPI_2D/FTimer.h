#pragma once
#include <chrono>
#include <thread>
#include "CommonInclude.h"

namespace LJG
{
	constexpr float TickFrequency = 60 / 1000.f;

	class FTimer
	{
	public:
		FTimer();
		
		void Reset();

		/** 경과 시간 (초) 반환*/
		float ElapsedSeconds();

		/** 1/1000초 반환 */
		float ElapsedMillis();

		static void SetTimer(std::function<void()> Callback, float InDelaySeconds);
	private:
		time_point<high_resolution_clock> mStartTime;
	};
}

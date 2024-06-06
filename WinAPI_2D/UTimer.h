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

		/** ��� �ð� (��) ��ȯ*/
		float ElapsedSeconds();

		/** 1/1000�� ��ȯ */
		float ElapsedMillis();

	private:
		time_point<high_resolution_clock> mStartTime;

		// static LARGE_INTEGER CpuFrequency;// CPU ���� ���ļ�
		// static LARGE_INTEGER PrevFrequency; // ���� Ŭ�� ����
		// static LARGE_INTEGER CurrentFrequency; // ���� Ŭ�� ����
	};
}

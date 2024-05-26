#include "Timer.h"

namespace LJG
{
	namespace Utils
	{
		// LARGE_INTEGER Timer::CpuFrequency     = {};
		// LARGE_INTEGER Timer::PrevFrequency    = {};
		// LARGE_INTEGER Timer::CurrentFrequency = {};

		Timer::Timer()
		{
			Reset();
		}

		/*
		bool Timer::Initialize()
		{
			QueryPerformanceFrequency(&CpuFrequency);

			if (CpuFrequency.QuadPart == 0)
			{
				LOG_CORE_WARN("���ػ�Ÿ�̸� ���� X");
				return false;
			}

			QueryPerformanceFrequency(&PrevFrequency);

			mUpdateTimer = ElapsedMillis();

			return true;
		}

		void Timer::Update()
		{
			QueryPerformanceCounter(&CurrentFrequency); // ���� Ŭ�� ����(Perforrmance)�� ��ȯ

			// (���� - ����) ���� �� (QuadPart)�� ���� ��
			const float differentFreq = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

			// (���� - ����) ī���� / ���� ���ļ��� ���� �� 
			DeltaTimeValue = differentFreq / static_cast<float>(CpuFrequency.QuadPart);

			PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
		}

		void Timer::Render(HDC Hdc)
		{
			static float time = 0.f;
			time += DeltaTimeValue;


			const float fps = 1.f / DeltaTimeValue;
		}*/


		void Timer::Reset()
		{
			mStartTime = high_resolution_clock::now();
		}

		float Timer::ElapsedSeconds()
		{
			return ElapsedMillis() / 1000.f;
		}

		float Timer::ElapsedMillis()
		{
			return duration_cast<duration<float, std::milli>>(high_resolution_clock::now() - mStartTime).count();
		}
	}
}

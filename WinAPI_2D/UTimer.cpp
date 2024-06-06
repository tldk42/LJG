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
			LOG_CORE_WARN("���ػ�Ÿ�̸� ���� X");
			return false;
		}

		QueryPerformanceFrequency(&PrevFrequency);

		mUpdateTimer = ElapsedMillis();

		return true;
	}

	void UTimer::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency); // ���� Ŭ�� ����(Perforrmance)�� ��ȯ

		// (���� - ����) ���� �� (QuadPart)�� ���� ��
		const float differentFreq = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		// (���� - ����) ī���� / ���� ���ļ��� ���� �� 
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

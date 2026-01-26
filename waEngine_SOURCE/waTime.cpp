#include "waTime.h"

namespace wa
{
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurFrequency = {};
	float Time::DeltaTime = 0.0f;

	void Time::Initialize()
	{
		// Cpu 고유 진동수
		QueryPerformanceFrequency(&CpuFrequency);

		// 프로그램이 시작 했을 때 현재 진동수
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurFrequency);

		float differenceFrequency = static_cast<float>(CurFrequency.QuadPart - PrevFrequency.QuadPart);
		DeltaTime = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);
		PrevFrequency = CurFrequency;
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;

		time += DeltaTime;
		float fps = 1.0f / DeltaTime;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"Time : %d", (int)fps);
		int len = wcsnlen_s(str, 50);


		TextOut(hdc, 0, 0, str, len);

	}
}
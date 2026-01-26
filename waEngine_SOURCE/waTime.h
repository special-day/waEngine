#pragma once
#include "CommonInclude.h"

namespace wa
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static float DT() { return DeltaTime; }

	private:
		static LARGE_INTEGER CpuFrequency;
		static LARGE_INTEGER PrevFrequency;
		static LARGE_INTEGER CurFrequency;
		static float DeltaTime;

	};
}


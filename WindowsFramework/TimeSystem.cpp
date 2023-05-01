#include "WinApp.h"
#include "TimeSystem.h"
#include <cmath>

namespace time
{
	ULONGLONG previousTime;
	ULONGLONG currentTime;
	ULONGLONG deltaTime;

	void InitTime()
	{
		previousTime = currentTime = GetTickCount64();
	}

	void UpdateTime()
	{
		previousTime = currentTime;

		currentTime = GetTickCount64();

		deltaTime = currentTime - previousTime;
	}

	const float GetFrameRate()
	{
		if (deltaTime == 0) return 0;

		return deltaTime / 1000;
	}

	const ULONGLONG GetDeltaTime() { return deltaTime; }

}
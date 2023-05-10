#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

#include "TimeManager.h"

namespace hockman
{
	TimeManager* TimeManager::mInstance = nullptr;

	TimeManager* TimeManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new TimeManager();
		}

		return mInstance;
	}

	void TimeManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	TimeManager::TimeManager()
		: mFPS(0)
		, mFrameCount(0)
		, mDeltaTime(0.f)
	{
		Init();
	}

	void TimeManager::Init()
	{
		QueryPerformanceFrequency(&mFrequency);
		QueryPerformanceCounter(&mCurTime);
		mPrevTime = mCurTime;
		mFPS = 0;
		mFrameCount = 0;
	}

	void TimeManager::Frame()
	{
		static float sTime = 0.f;

		sTime += GetDeltaTime();

		char buf[64];
		sprintf(buf, "fps : %d, DeltaTime : %.5f\n", mFPS, GetDeltaTime());
 		OutputDebugStringA(buf);

		if (sTime >= 1.f)
		{
			sTime -= 1.f;
			mFPS = mFrameCount;
			mFrameCount = 0;
		}

		mDeltaTime = (float)(mCurTime.QuadPart - mPrevTime.QuadPart) / mFrequency.QuadPart;
		mPrevTime = mCurTime;
		QueryPerformanceCounter(&mCurTime);
		++mFrameCount;
	}
}
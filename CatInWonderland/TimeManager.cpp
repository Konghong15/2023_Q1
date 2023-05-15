#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

#include "TimeManager.h"

namespace catInWonderland
{
	TimeManager* TimeManager::mInstance = nullptr;

	TimeManager* TimeManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new TimeManager();
			mInstance->Reset();
		}

		return mInstance;
	}

	void TimeManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void TimeManager::Reset()
	{
		QueryPerformanceFrequency(&mFrequency);
		QueryPerformanceCounter(&mCurTime);
		mDeltaTime = 0.f;
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
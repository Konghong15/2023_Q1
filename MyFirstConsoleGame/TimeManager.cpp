#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

#include "TimeManager.h"

namespace hongpireSurvivors
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
		: mCurTime(0)
		, mPrevTime(0)
		, mFrameCount(0)
		, mFPS(0)
	{
	}

	void TimeManager::Init()
	{
		mCurTime = GetTickCount64();
		mPrevTime = mCurTime;
		mFPS = 0;
		mFrameCount = 0;
	}

	void TimeManager::Frame()
	{
		static float sTime = 0.f;

		sTime += GetDeltaTime();

		if (sTime >= 1.f)
		{
			char buf[30];
			sprintf(buf, "fps : %d\n", mFPS);
			OutputDebugStringA(buf);
			sTime -= 1.f;
			mFPS = mFrameCount;
			mFrameCount = 0;
		}

		mPrevTime = mCurTime;
		mCurTime = GetTickCount64();
		++mFrameCount;
	}
}
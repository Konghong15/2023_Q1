#pragma once

#include <Windows.h>

namespace catInWonderland
{
	class TimeManager
	{
	public:
		static TimeManager* GetInstance();
		static void DeleteInstance();

		void Reset();
		void Frame();

		inline float GetDeltaTime();
		inline unsigned int GetFPS();

	private:
		TimeManager() = default;
		~TimeManager() = default;

	private:
		static TimeManager* mInstance;

		LARGE_INTEGER mCurTime;
		LARGE_INTEGER mPrevTime;
		LARGE_INTEGER mFrequency;
		unsigned int mFrameCount;
		unsigned int mFPS;

		float mDeltaTime;
	};

	float TimeManager::GetDeltaTime()
	{
		return  mDeltaTime > 0.03f ? 0.03f : mDeltaTime;
	}

	unsigned int TimeManager::GetFPS()
	{
		return mFPS;
	}
}
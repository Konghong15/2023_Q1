#pragma once

#include <Windows.h>

namespace hockman
{
	class TimeManager
	{
	public:
		static TimeManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Frame();

		inline float GetDeltaTime();
		inline unsigned int GetFPS();

	private:
		TimeManager();
		~TimeManager() = default;

	private:
		static TimeManager* mInstance;

		ULONGLONG mCurTime;
		ULONGLONG mPrevTime;
		unsigned int mFrameCount;
		unsigned int mFPS;
	};

	float TimeManager::GetDeltaTime()
	{
		float deltaTime = (mCurTime - mPrevTime) / 1000.f;
		return  deltaTime > 0.03f ? 0.03f : deltaTime;
	}

	unsigned int TimeManager::GetFPS()
	{
		return mFPS;
	}
}
#pragma once

#include <Windows.h>

namespace hongpireSurvivors
{
	class TimeManager
	{
	public:
		static TimeManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Frame();

		inline ULONGLONG GetElapsedTime();
		inline float GetDeltaTime();
		inline unsigned int GetFPS();

	private:
		TimeManager();
		~TimeManager() = default;

	private:
		enum { KEY_SIZE = 255 };
		static TimeManager* mInstance;

		ULONGLONG mElapsedTime;
		ULONGLONG mCurTime;
		ULONGLONG mPrevTime;
		unsigned int mFrameCount;
		unsigned int mFPS;
	};

	ULONGLONG TimeManager::GetElapsedTime()
	{
		return mElapsedTime;
	}

	float TimeManager::GetDeltaTime()
	{
		float deltaTime = (mCurTime - mPrevTime) / 1000.f;
		return  deltaTime > 0.03 ? 0.03 : deltaTime;
	}

	unsigned int TimeManager::GetFPS()
	{
		return mFPS;
	}
}
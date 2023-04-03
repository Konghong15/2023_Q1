#pragma once
#pragma once

#include <Windows.h>

namespace hongpireSurvivors
{
	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager() = default;

		static TimeManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Frame();

		inline ULONGLONG GetElapsedTime();
		inline ULONGLONG GetDeltaTime();
		inline unsigned int GetFPS();

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

	ULONGLONG TimeManager::GetDeltaTime()
	{
		return mCurTime - mPrevTime;
	}

	unsigned int TimeManager::GetFPS()
	{
		return mFPS;
	}
}
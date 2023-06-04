#pragma once

#include <Windows.h>

namespace catInWonderland
{
	class TimeManager final
	{
	public:
		TimeManager();
		~TimeManager() = default;
		TimeManager(const TimeManager&) = delete;
		TimeManager& operator=(const TimeManager&) = delete;

		void Init();
		void Update();

		inline unsigned int GetFrameRate() const;
		inline float GetDeltaTime() const;

	private:
		ULONGLONG mCurrentTime;
		ULONGLONG mPreviousTime;
		float mDeltaTime;
		float mElapsed;
		unsigned int mFPS;
		unsigned int mFrameCount;
	};

	unsigned int TimeManager::GetFrameRate() const
	{
		return mFPS;
	}

	float TimeManager::GetDeltaTime() const
	{
		return mDeltaTime;
	}
}
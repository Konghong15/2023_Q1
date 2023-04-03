#pragma once

#include <Windows.h>

namespace hongpireSurvivors
{
	enum class eBufferIndex
	{
		FRONT = 0,
		BACK = 1,
		SIZE = 2
	};

	class RenderManager
	{
	public:
		static RenderManager* GetInstance();
		static void DeleteInstance();

		void Render();

	private:
		RenderManager();
		~RenderManager();

		void swapBuffer();
		void clearBuffer();
		inline int getScreenWidth() const;
		inline int getScreenHeight() const;

	private:
		enum { KEY_SIZE = 255 };
		static RenderManager* mInstance;

		HANDLE mScreen[static_cast<int>(eBufferIndex::SIZE)];
		eBufferIndex mBufferIndex;
		SMALL_RECT mScreenSize;
	};

	int RenderManager::getScreenWidth() const
	{
		return mScreenSize.Right - mScreenSize.Left;
	}

	int RenderManager::getScreenHeight() const
	{
		return mScreenSize.Bottom - mScreenSize.Top;
	}
}
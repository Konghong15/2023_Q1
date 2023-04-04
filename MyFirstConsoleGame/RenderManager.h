#pragma once

#include <Windows.h>
#include "eSpriteType.h"

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

		void Draw(int x, int y, const char c);
		void Draw(int x, int y, eSpriteType spriteType);
		void Render();

	private:
		RenderManager();
		~RenderManager();

		void swapBuffer();
		void clearBuffer();
		inline int getScreenWidth() const;
		inline int getScreenHeight() const;
		inline HANDLE& getCurrentHandle();

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

	HANDLE& RenderManager::getCurrentHandle()
	{
		return mScreen[static_cast<int>(mBufferIndex)];
	}
}
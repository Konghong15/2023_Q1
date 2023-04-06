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
		void Draw(int x, int y, eSpriteType spriteType, bool isLeft = false);
		void Render();

		inline int GetScreenWidth() const;
		inline int GetScreenHeight() const;

	private:
		RenderManager();
		~RenderManager();

		void swapBuffer();
		void clearBuffer();
		inline HANDLE& getCurrentHandle();

	private:
		enum { KEY_SIZE = 255 }; // font size 10 : { 426, 79 }
		enum { BUFFER_X_OFFSET = 12 }; // font size 10 : { 426, 79 }
		enum { BUFFER_WIDTH = 426 }; // font size 10 : { 426, 79 }
		enum { BUFFER_HEIGHT = 79 }; // font size 6 : { 680, 133 }
		static RenderManager* mInstance;

		char(*mBuffer)[BUFFER_WIDTH];
		HANDLE mScreen[static_cast<int>(eBufferIndex::SIZE)];
		eBufferIndex mBufferIndex;
		SMALL_RECT mScreenSize;
	};

	int RenderManager::GetScreenWidth() const
	{
		return mScreenSize.Right - mScreenSize.Left;
	}

	int RenderManager::GetScreenHeight() const
	{
		return mScreenSize.Bottom - mScreenSize.Top;
	}

	HANDLE& RenderManager::getCurrentHandle()
	{
		return mScreen[static_cast<int>(mBufferIndex)];
	}
}
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

	enum class eConsoleColor
	{
		BLACK = 0,
		DEEP_BLUE = 1,
		DEEP_GREEN = 2,
		DEEP_MINT = 3,
		DEEP_RED = 4,
		DEEP_PINK = 5,
		DEEP_YELLOW = 6,
		DEEP_WHITE = 7,
		GRAY = 8,
		BLUE = 9,
		GREEN = 10,
		MINT = 11,
		RED = 12,
		PINK = 13,
		YELLOW = 14,
		WHITE = 15
	};

	class Sprite;

	class RenderManager
	{
	public:
		static RenderManager* GetInstance();
		static void DeleteInstance();

		void Draw(int x, int y, eSpriteType spriteType, WORD color = 0, bool isLeft = false);
		void DrawMap(eSpriteType left, eSpriteType right, int camaraX, WORD color);
		void Render();

		inline int GetScreenWidth() const;
		inline int GetScreenHeight() const;
		inline WORD GetColor(eConsoleColor background, eConsoleColor font);

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
		WORD(*mColorBuffer)[BUFFER_WIDTH];
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

	WORD RenderManager::GetColor(eConsoleColor background, eConsoleColor font)
	{
		return static_cast<WORD>(background) << 4 | static_cast<WORD>(font);
	}
}
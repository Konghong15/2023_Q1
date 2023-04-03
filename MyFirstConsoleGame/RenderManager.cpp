#include "RenderManager.h"

namespace hongpireSurvivors
{
	RenderManager* RenderManager::mInstance = nullptr;

	RenderManager* RenderManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new RenderManager();
		}

		return mInstance;
	}

	void RenderManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void RenderManager::Render()
	{

	}

	RenderManager::RenderManager()
		: mBufferIndex(eBufferIndex::FRONT)
	{
		mScreen[static_cast<int>(eBufferIndex::FRONT)] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		mScreen[static_cast<int>(eBufferIndex::BACK)] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = 0;
		cursorInfo.dwSize = 1;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		mScreenSize.Left = csbi.srWindow.Left;
		mScreenSize.Right = csbi.srWindow.Right;
		mScreenSize.Bottom = csbi.srWindow.Bottom;
		mScreenSize.Top = csbi.srWindow.Top;
	}

	RenderManager::~RenderManager()
	{
		CloseHandle(mScreen[static_cast<int>(eBufferIndex::FRONT)]);
		CloseHandle(mScreen[static_cast<int>(eBufferIndex::BACK)]);
	}

	void RenderManager::swapBuffer()
	{
		mBufferIndex = mBufferIndex == eBufferIndex::FRONT ? eBufferIndex::BACK : eBufferIndex::FRONT;
	}

	void RenderManager::clearBuffer()
	{
		COORD coordi = { 0, };
		coordi.X = mScreenSize.Left;
		DWORD dw;

		for (coordi.Y = mScreenSize.Top; coordi.Y < getScreenHeight(); ++coordi.Y)
		{
			FillConsoleOutputCharacter(mScreen[static_cast<int>(mBufferIndex)], ' ', getScreenWidth(), coordi, &dw);
		}
	}
}
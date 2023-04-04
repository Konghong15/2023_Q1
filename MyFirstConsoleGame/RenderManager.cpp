#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

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

	void RenderManager::Draw(int x, int y, const char ch)
	{
		COORD coodi = { x, y };
		DWORD dw;
		char str[10] = { 0, };
		str[0] = ch;

		SetConsoleCursorPosition(getCurrentHandle(), coodi);
		WriteFile(getCurrentHandle(), str, 1, &dw, NULL);
	}

	void RenderManager::Draw(int x, int y, eSpriteType spriteType)
	{
		COORD coodi = { x, y };
		DWORD dw;

		const Sprite& sp = SpriteManager::GetInstance()->GetSprite(spriteType);
		const char* img_ptr = sp.Img;

		for (int i = 0; i < sp.Height - 2; ++i)
		{
			SetConsoleCursorPosition(getCurrentHandle(), coodi);
			WriteFile(getCurrentHandle(), img_ptr, sp.Width, &dw, NULL);

			img_ptr += sp.Width + 1;
			++coodi.Y;
		}
	}

	void RenderManager::Render()
	{
		swapBuffer();
		clearBuffer();
	}

	RenderManager::RenderManager()
		: mBufferIndex(eBufferIndex::FRONT)
	{
		mScreen[static_cast<int>(eBufferIndex::FRONT)] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		mScreen[static_cast<int>(eBufferIndex::BACK)] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = 0;
		cursorInfo.dwSize = 1;
		SetConsoleCursorInfo(mScreen[static_cast<int>(eBufferIndex::FRONT)], &cursorInfo);
		SetConsoleCursorInfo(mScreen[static_cast<int>(eBufferIndex::BACK)], &cursorInfo);

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
		SetConsoleActiveScreenBuffer(getCurrentHandle());
		mBufferIndex = mBufferIndex == eBufferIndex::FRONT ? eBufferIndex::BACK : eBufferIndex::FRONT;
	}

	void RenderManager::clearBuffer()
	{
		COORD coordi = { 0, };
		coordi.X = mScreenSize.Left;
		DWORD dw;

		for (coordi.Y = mScreenSize.Top; coordi.Y < getScreenHeight(); ++coordi.Y)
		{
			FillConsoleOutputCharacter(getCurrentHandle(), ' ', getScreenWidth(), coordi, &dw);
		}
	}
}
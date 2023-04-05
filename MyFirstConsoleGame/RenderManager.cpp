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
		const Sprite& sp = SpriteManager::GetInstance()->GetSprite(spriteType);

		for (int i = 0; i < (sp.Height - 1) * sp.Width; ++i)
		{
			int yi = y + (i / sp.Width);
			int xi = x + (i % sp.Width) + BUFFER_X_OFFSET;

			if (sp.Img[i] != ' ')
			{
				mBuffer[yi][xi] = sp.Img[i];
			}
		}
	}

	void RenderManager::Render()
	{
		DWORD dw;

		SetConsoleCursorPosition(getCurrentHandle(), { 0, 0 });
		WriteFile(getCurrentHandle(), mBuffer, BUFFER_HEIGHT * BUFFER_WIDTH, &dw, NULL);
		swapBuffer();
		clearBuffer();
	}

	RenderManager::RenderManager()
		: mBufferIndex(eBufferIndex::FRONT)
		, mBuffer{ 0, }
	{
		mScreen[static_cast<int>(eBufferIndex::FRONT)] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		mScreen[static_cast<int>(eBufferIndex::BACK)] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = 0;
		cursorInfo.dwSize = 1;
		SetConsoleCursorInfo(mScreen[static_cast<int>(eBufferIndex::FRONT)], &cursorInfo);
		SetConsoleCursorInfo(mScreen[static_cast<int>(eBufferIndex::BACK)], &cursorInfo);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { BUFFER_WIDTH, BUFFER_HEIGHT });
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		mScreenSize.Left = csbi.srWindow.Left;
		mScreenSize.Right = csbi.srWindow.Right;
		mScreenSize.Bottom = csbi.srWindow.Bottom;
		mScreenSize.Top = csbi.srWindow.Top;
		mBuffer = new char[BUFFER_HEIGHT][BUFFER_WIDTH];
		memset(mBuffer, ' ', BUFFER_HEIGHT * BUFFER_WIDTH);
	}

	RenderManager::~RenderManager()
	{
		CloseHandle(mScreen[static_cast<int>(eBufferIndex::FRONT)]);
		CloseHandle(mScreen[static_cast<int>(eBufferIndex::BACK)]);
		delete[] mBuffer;
	}

	void RenderManager::swapBuffer()
	{
		SetConsoleActiveScreenBuffer(getCurrentHandle());
		mBufferIndex = mBufferIndex == eBufferIndex::FRONT ? eBufferIndex::BACK : eBufferIndex::FRONT;
	}

	void RenderManager::clearBuffer()
	{
		//COORD coordi = { 0, };
		//coordi.X = mScreenSize.Left;
		//DWORD dw;
		memset(mBuffer, ' ', BUFFER_HEIGHT * BUFFER_WIDTH);
		Draw(0, 0, eSpriteType::MAP_1);
		//for (coordi.Y = mScreenSize.Top; coordi.Y < GetScreenHeight(); ++coordi.Y)
		//{
		//	FillConsoleOutputCharacter(getCurrentHandle(), ' ', GetScreenWidth(), coordi, &dw);
		//}
	}
}
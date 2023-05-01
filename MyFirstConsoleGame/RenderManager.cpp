#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "ObjectManager.h"

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

	WORD RenderManager::GetColor(eConsoleColor background, eConsoleColor font)
	{
		return static_cast<WORD>(background) << 4 | static_cast<WORD>(font);
	}

	void RenderManager::DrawMap(eSpriteType spriteType, const COORD& sceneSize, const COORD& camaraPos, WORD color)
	{
		const Sprite& sp = SpriteManager::GetInstance()->GetSprite(spriteType);
		const int MAX_Y = BUFFER_HEIGHT < sceneSize.Y ? BUFFER_HEIGHT : sceneSize.Y;

		for (int i = 0; i < MAX_Y; ++i)
		{
			for (int j = BUFFER_X_OFFSET; j < BUFFER_WIDTH - BUFFER_X_OFFSET; ++j)
			{
				int yi = i;
				int xi = j;

				if (yi >= BUFFER_HEIGHT || xi >= BUFFER_WIDTH)
				{
					continue;
				}

				int spIndex = (camaraPos.Y + i) * sp.Width + (camaraPos.X + j);

				if (sp.Img[spIndex] != ' ')
				{
					assert(yi < BUFFER_HEIGHT&& xi < BUFFER_WIDTH);
					mBuffer[yi][xi] = sp.Img[spIndex];
					mColorBuffer[yi][xi] = color;
				}
			}
		}
	}

	void RenderManager::DrawRect(int x, int y, int w, int h, char ch, WORD color)
	{
		for (int i = x; i < x + w; ++i)
		{
			mBuffer[y][i] = ch;
			mBuffer[y + h][i] = ch;
			mColorBuffer[y][i] = color;
			mColorBuffer[y + h][i] = color;
		}

		for (int i = y; i < y + h; ++i)
		{
			mBuffer[i][x] = ch;
			mBuffer[i][x + w] = ch;
			mColorBuffer[i][x] = color;
			mColorBuffer[i][x + w] = color;
		}
	}

	void RenderManager::Draw(int x, int y, eSpriteType spriteType, WORD color, bool isLeft)
	{
		const Sprite& sp = SpriteManager::GetInstance()->GetSprite(spriteType);

		if (!isLeft)
		{
			for (int i = 0; i < sp.Height * sp.Width; ++i)
			{
				int yi = y + (i / sp.Width);
				int xi = x + (i % sp.Width) + BUFFER_X_OFFSET;

				if (yi >= BUFFER_HEIGHT || xi >= BUFFER_WIDTH)
				{
					continue;
				}

				if (sp.Img[i] != ' ')
				{
					assert(yi < BUFFER_HEIGHT&& xi < BUFFER_WIDTH);
					mBuffer[yi][xi] = sp.Img[i];
					mColorBuffer[yi][xi] = color;
				}
			}
		}
		else
		{
			for (int i = 0; i < sp.Height * sp.Width; ++i)
			{
				int yi = y + (i / sp.Width);
				int xi = x + (sp.Width - (i % sp.Width)) + BUFFER_X_OFFSET;

				if (yi >= BUFFER_HEIGHT || xi >= BUFFER_WIDTH)
				{
					continue;
				}

				if (sp.Img[i] != ' ')
				{
					assert(yi < BUFFER_HEIGHT&& xi < BUFFER_WIDTH);
					mBuffer[yi][xi] = sp.Img[i];
					mColorBuffer[yi][xi] = color;
				}
			}
		}
	}

	void RenderManager::Render()
	{
		DWORD dw;

		SetConsoleCursorPosition(getCurrentHandle(), { 0, 0 });
		GetConsoleScreenBufferInfo(getCurrentHandle(), &mScreenInfo);
		WriteFile(getCurrentHandle(), mBuffer, BUFFER_HEIGHT * BUFFER_WIDTH, &dw, NULL);

		const WORD* wordPtr = static_cast<const WORD*>(mColorBuffer[0]);
		WriteConsoleOutputAttribute(getCurrentHandle(), wordPtr, BUFFER_HEIGHT * BUFFER_WIDTH, { 0, 0 }, &dw);

		swapBuffer();
		clearBuffer();
	}

	RenderManager::RenderManager()
		: mBufferIndex(eBufferIndex::FRONT)
		, mBuffer{ 0, }
		, mScreenInfo{ 0, }
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
		SetConsoleScreenBufferSize(mScreen[static_cast<int>(eBufferIndex::FRONT)], { BUFFER_WIDTH, BUFFER_HEIGHT });
		SetConsoleScreenBufferSize(mScreen[static_cast<int>(eBufferIndex::BACK)], { BUFFER_WIDTH, BUFFER_HEIGHT });
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		mScreenSize.Left = csbi.srWindow.Left;
		mScreenSize.Right = csbi.srWindow.Right;
		mScreenSize.Bottom = csbi.srWindow.Bottom;
		mScreenSize.Top = csbi.srWindow.Top;

		// assert(GetScreenWidth() == BUFFER_WIDTH && GetScreenHeight() == BUFFER_HEIGHT);

		mBuffer = new char[BUFFER_HEIGHT][BUFFER_WIDTH];
		mColorBuffer = new WORD[BUFFER_HEIGHT][BUFFER_WIDTH];
		memset(mBuffer, ' ', BUFFER_HEIGHT* BUFFER_WIDTH);
		memset(mColorBuffer, GetColor(eConsoleColor::BLACK, eConsoleColor::BLACK), BUFFER_HEIGHT* BUFFER_WIDTH * sizeof(WORD));
	}

	RenderManager::~RenderManager()
	{
		CloseHandle(mScreen[static_cast<int>(eBufferIndex::FRONT)]);
		CloseHandle(mScreen[static_cast<int>(eBufferIndex::BACK)]);
		delete[] mBuffer;
		delete[] mColorBuffer;
	}

	void RenderManager::swapBuffer()
	{
		SetConsoleActiveScreenBuffer(getCurrentHandle());
		mBufferIndex = mBufferIndex == eBufferIndex::FRONT ? eBufferIndex::BACK : eBufferIndex::FRONT;
	}

	void RenderManager::clearBuffer()
	{
		memset(mColorBuffer, GetColor(eConsoleColor::BLACK, eConsoleColor::BLACK), BUFFER_HEIGHT * BUFFER_WIDTH * sizeof(WORD));
		memset(mBuffer, ' ', BUFFER_HEIGHT * BUFFER_WIDTH);

		/*COORD camara = ObjectManager::GetInstance()->GetCamara();
		DrawMap(eSpriteType::MAP_1_0, eSpriteType::MAP_1_1, camara.X, GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_GREEN));*/
	}
}
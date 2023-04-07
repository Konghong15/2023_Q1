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

	void RenderManager::Draw(int x, int y, eSpriteType spriteType, bool isLeft)
	{
		const Sprite& sp = SpriteManager::GetInstance()->GetSprite(spriteType);

		if (!isLeft)
		{
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
		else
		{
			for (int i = 0; i < (sp.Height - 1) * sp.Width; ++i)
			{
				int yi = y + (i / sp.Width);
				int xi = x + (sp.Width - (i % sp.Width)) + BUFFER_X_OFFSET;

				if (sp.Img[i] != ' ')
				{
					mBuffer[yi][xi] = sp.Img[i];
				}
			}
		}

		switch (spriteType)
		{
		case hongpireSurvivors::eSpriteType::PLAYER_IDLE:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::PLAYER_RUN:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::PLAYER_ATTACK:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::PROJECTIE:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::PLAYER_JUMP:
			setColor(x, y, sp, getColor(eConsoleColor::BLACK, eConsoleColor::DEEP_YELLOW), isLeft);
			break;
		case hongpireSurvivors::eSpriteType::MAP_1:
			setColor(x, y, sp, getColor(eConsoleColor::BLACK, eConsoleColor::DEEP_GREEN), isLeft);
			break;
		case hongpireSurvivors::eSpriteType::ENEMY_0:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::ENEMY_1:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::ENEMY_1_PROJECTILE:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::ENEMY_2:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_0_IDLE:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_0_JUMP:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_1_IDLE:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_1_ATTACK:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_2_IDLE:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_2_ATTACK:
			/* intentional fall-through */
		case hongpireSurvivors::eSpriteType::BOSS_2_PROJECTILE:
			setColor(x, y, sp, getColor(eConsoleColor::BLACK, eConsoleColor::RED), isLeft);
			break;
		default:
			assert(false);
			break;
		}
	}

	void RenderManager::Render()
	{
		DWORD dw;

		SetConsoleCursorPosition(getCurrentHandle(), { 0, 0 });
		WriteFile(getCurrentHandle(), mBuffer, BUFFER_HEIGHT * BUFFER_WIDTH, &dw, NULL);
		WriteConsoleOutputAttribute(getCurrentHandle(), static_cast<const WORD*>(mColorBuffer[0]), BUFFER_HEIGHT * BUFFER_WIDTH, { 0, 0 }, &dw);

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
		memset(mBuffer, ' ', BUFFER_HEIGHT * BUFFER_WIDTH);
		memset(mColorBuffer, getColor(eConsoleColor::BLACK, eConsoleColor::BLACK), BUFFER_HEIGHT * BUFFER_WIDTH * sizeof(WORD));
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
		//COORD coordi = { 0, };
		//coordi.X = mScreenSize.Left;
		//DWORD dw;
		memset(mColorBuffer, getColor(eConsoleColor::BLACK, eConsoleColor::BLACK), BUFFER_HEIGHT * BUFFER_WIDTH * sizeof(WORD));
		memset(mBuffer, ' ', BUFFER_HEIGHT * BUFFER_WIDTH);
		Draw(0, 0, eSpriteType::MAP_1);
		//for (coordi.Y = mScreenSize.Top; coordi.Y < GetScreenHeight(); ++coordi.Y)
		//{
		//	FillConsoleOutputCharacter(getCurrentHandle(), ' ', GetScreenWidth(), coordi, &dw);
		//}
	}

	void RenderManager::setColor(int x, int y, const Sprite& sprite, WORD color, bool isLeft)
	{
		if (!isLeft)
		{
			for (int i = 0; i < (sprite.Height - 1) * sprite.Width; ++i)
			{
				int yi = y + (i / sprite.Width);
				int xi = x + (i % sprite.Width) + BUFFER_X_OFFSET;

				if (sprite.Img[i] != ' ')
				{
					mColorBuffer[yi][xi] = color;
				}
			}
		}
		else
		{
			for (int i = 0; i < (sprite.Height - 1) * sprite.Width; ++i)
			{
				int yi = y + (i / sprite.Width);
				int xi = x + (sprite.Width - (i % sprite.Width)) + BUFFER_X_OFFSET;

				if (sprite.Img[i] != ' ')
				{
					mColorBuffer[yi][xi] = color;
				}
			}
		}
	}
}
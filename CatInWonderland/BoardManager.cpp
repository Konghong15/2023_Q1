#include <cassert>

#include "BoardManager.h"
#include "WinApp.h"

namespace catInWonderland
{
	BoardManager* BoardManager::mInstance = nullptr;

	BoardManager* BoardManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new BoardManager();
			mInstance->init();
		}

		return mInstance;
	}

	void BoardManager::DeleteInstance()
	{
		mInstance->release();
		delete mInstance;
		mInstance = nullptr;
	}

	void BoardManager::init()
	{
		mWorldRectangles.reserve(static_cast<size_t>(MAX_BOARD_SIZE * MAX_BOARD_SIZE));
		mBoardSize = 0;
	}

	void BoardManager::release()
	{
		mWorldRectangles.clear();
		mBoardSize = 0;
	}

	void BoardManager::SetBoardSize(size_t size)
	{
		const size_t WND_WIDTH = WinApp::GetWidth();
		const size_t WND_HEIGHT = WinApp::GetHeight();
		const float CELL_WIDTH = (WND_WIDTH - BOARD_PADDING * 2) / static_cast<float>(size);
		const float CELL_HEIGHT = (WND_HEIGHT - BOARD_PADDING * 2) / static_cast<float>(size);
		const float CELL_SIDE = CELL_WIDTH < CELL_HEIGHT ? CELL_WIDTH : CELL_HEIGHT;
		const float START_X = WND_WIDTH / 2 - (CELL_SIDE * size / 2.f);
		const float START_Y = WND_HEIGHT / 2 - (CELL_SIDE * size / 2.f);

		mWorldRectangles.clear();
		mBoardSize = size;

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				float x1 = CELL_SIDE * j + CELL_PADDING + START_X;
				float y1 = CELL_SIDE * i + CELL_PADDING + START_Y;
				float x2 = CELL_SIDE * (j + 1) - CELL_PADDING + START_X;
				float y2 = CELL_SIDE * (i + 1) - CELL_PADDING + START_Y;

				mWorldRectangles.emplace_back(x1, y1, x2, y2);
			}
		}
	}

	void BoardManager::RotateRight(size_t* outIndexX, size_t* outIndexY)
	{
		assert(outIndexX != nullptr && outIndexY != nullptr);
		assert(*outIndexX < mBoardSize && (*outIndexY) < mBoardSize);

		int y = *outIndexY;
		*outIndexY = *outIndexX;
		*outIndexX = mBoardSize - 1 - y;
	}

	void BoardManager::RotateLeft(size_t* outIndexX, size_t* outIndexY)
	{
		assert(outIndexX != nullptr && outIndexY != nullptr);
		assert(*outIndexX < mBoardSize && (*outIndexY) < mBoardSize);

		int x = *outIndexX;
		*outIndexX = *outIndexY;
		*outIndexY = mBoardSize - 1 - x;
	}
}
#include "BoardManager.h"
#include "WinApp.h"
#include "Vector2.h"

namespace catInWonderland
{
	BoardManager::BoardManager()
		: mBoardSize(0u)
		, mBoardPadding(0u)
		, mCellPadding(0u)
	{
		mWorldRectangles.reserve(RESERVE_SIZE);
	}

	void BoardManager::CreateBoard(size_t boardSize, size_t boardPadding, size_t cellPadding)
	{
		const size_t WND_WIDTH = WinApp::GetWidth();
		const size_t WND_HEIGHT = WinApp::GetHeight();

		mBoardSize = boardSize;
		mBoardPadding = boardPadding;
		mCellPadding = cellPadding;

		const float CELL_WIDTH = (WND_WIDTH - mBoardPadding * 2) / static_cast<float>(mBoardSize);
		const float CELL_HEIGHT = (WND_HEIGHT - mBoardPadding * 2) / static_cast<float>(mBoardSize);
		const float CELL_SIDE = CELL_WIDTH < CELL_HEIGHT ? CELL_WIDTH : CELL_HEIGHT;
		const float START_X = WND_WIDTH / 2 - (CELL_SIDE * mBoardSize / 2.f);
		const float START_Y = WND_HEIGHT / 2 - (CELL_SIDE * mBoardSize / 2.f);

		mWorldRectangles.clear();

		for (int i = 0; i < mBoardSize; ++i)
		{
			for (int j = 0; j < mBoardSize; ++j)
			{
				float x1 = CELL_SIDE * j + mCellPadding + START_X;
				float y1 = CELL_SIDE * i + mCellPadding + START_Y;
				float x2 = CELL_SIDE * (j + 1) - mCellPadding + START_X;
				float y2 = CELL_SIDE * (i + 1) - mCellPadding + START_Y;

				mWorldRectangles.emplace_back(x1, y1, x2, y2);
			}
		}
	}


}